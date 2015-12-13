// ndn-File-Consumer
// requests files (in chunks) from a Producer

#ifndef FILECONSUMER_H
#define FILECONSUMER_H

// for communication with NFD
#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>

// using boost for file-system handling / cmd_options
#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::program_options;

namespace ndn {
class FileConsumer : noncopyable
{
    public:
        FileConsumer(string interest_name, int interest_lifetime);
        void run();
        virtual ~FileConsumer();
    protected:
    private:
        void onData(const Interest& interest, const Data& data);
        void onTimeout(const Interest& interest);

        Face m_face;
        string interest_name;
        int interest_lifetime;
};
}   // end namespace ndn

#endif // FILECONSUMER_H
