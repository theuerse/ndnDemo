// ndn-File-Producer
// requests files / file-chunks from a Producer

#ifndef CONSUMER_H
#define CONSUMER_H

// for communication with NFD
#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>

// using boost for file-system handling / cmd_options
#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::program_options;

namespace ndn {
class Consumer
{
    public:
        Consumer(string interest_name, int interest_lifetime);
        void run();
        virtual ~Consumer();
    protected:
    private:
        void onData(const Interest& interest, const Data& data);
        void onTimeout(const Interest& interest);

        Face m_face;
        string interest_name;
        int interest_lifetime;
};
}   // end namespace ndn

#endif // CONSUMER_H
