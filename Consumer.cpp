#include "Consumer.h"
// public methods
ndn::Consumer::Consumer(string interest_name, int interest_lifetime)
{
    this->interest_name = interest_name;
    this->interest_lifetime = interest_lifetime;
}

ndn::Consumer::~Consumer()
{
    cout << "Bye you cruel world" << endl;
}

// register prefix on NFD
void ndn::Consumer::run()
{
    Interest interest(Name(this->interest_name));  // e.g. "/example/testApp/randomData"
    interest.setInterestLifetime(time::milliseconds(this->interest_lifetime));   // time::milliseconds(1000)
    interest.setMustBeFresh(true);

    m_face.expressInterest(interest,
                           bind(&ndn::Consumer::onData, this,  _1, _2),
                           bind(&ndn::Consumer::onTimeout, this, _1));

    cout << "Sending " << interest << endl;

    // processEvents will block until the requested data received or timeout occurs
    m_face.processEvents();
}


// private methods
// react to the reception of a reply from a Producer
void ndn::Consumer::onData(const Interest& interest, const Data& data)
{
    cout << "data-packet received: " << endl;

    const Block& block = data.getContent();
    std::cout.write((const char*)block.value(),block.value_size());
    cout << endl;
}

// react on the request / Interest timing out
void ndn::Consumer::onTimeout(const Interest& interest)
{
    cout << "Timeout " << interest << endl;
}


//
// Main entry-point
//
int main(int argc, char** argv)
{
  string appName = boost::filesystem::basename(argv[0]);

  options_description desc("Programm Options");
  desc.add_options ()
      ("name,p", value<string>()->required (), "The name of the interest to be sent (Required)")
      ("lifetime,s", value<int>(), "The lifetime of the interest in milliseconds. (Default 1000ms)");

  positional_options_description positionalOptions;
  variables_map vm;

  try
  {
    store(command_line_parser(argc, argv).options(desc)
                .positional(positionalOptions).run(),
              vm); // throws on error

    notify(vm); //notify if required parameters are not provided.
  }
  catch(boost::program_options::required_option& e)
  {
    // user forgot to provide a required option
    cerr << "name           ... The name of the interest to be sent (Required)" << endl;
    cerr << "lifetime       ... The lifetime of the interest in milliseconds. (Default 1000ms)" << endl;
    cerr << "usage-example: " << "./" << appName << " --name /example/testApp/randomData" << endl;
    cerr << "usage-example: " << "./" << appName << " --name /example/testApp/randomData --lifetime 1000" << endl;

    cerr << "ERROR: " << e.what() << endl << endl;
    return -1;
  }
  catch(boost::program_options::error& e)
  {
    // a given parameter is faulty (e.g. given a string, asked for int)
    cerr << "ERROR: " << e.what() << endl << endl;
    return -1;
  }
  catch(exception& e)
  {
    cerr << "Unhandled Exception reached the top of main: "
              << e.what() << ", application will now exit" << endl;
    return -1;
  }

  int lifetime = 1000;
  if(vm.count ("lifetime"))
  {
    lifetime = vm["lifetime"].as<int>();
  }

  // create new Consumer instance with given parameters
  ndn::Consumer consumer(vm["name"].as<string>(),lifetime);

  try
  {
    // start producer
    consumer.run();
  }
  catch (const exception& e)
  {
    // shit happens
    cerr << "ERROR: " << e.what() << endl;
  }

  return 0;
}
