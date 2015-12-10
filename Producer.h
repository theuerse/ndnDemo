// ndn-File-Producer
// works like a simple http-server

#ifndef PRODUCER_H
#define PRODUCER_H

// for communication with NFD
#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>

// using boost for file-system handling / cmd_options
#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::program_options;

namespace ndn {
class Producer
{
    public:
        Producer(string prefix, int data_size, int freshness_seconds);
        void run();
        virtual ~Producer();
    protected:
    private:
        string generateContent(const int length);
        void onInterest(const InterestFilter& filter, const Interest& interest);
        void onRegisterFailed(const Name& prefix, const std::string& reason);

        Face m_face;
        KeyChain m_keyChain;
        string prefix;
        int data_size;
        int freshness_seconds;
};
}   // end namespace ndn

#endif // PRODUCER_H
