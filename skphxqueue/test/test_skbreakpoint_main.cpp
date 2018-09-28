#include <iostream>

#include "skphxqueue/comm.h"
#include "skphxqueue/plugin.h"


using namespace skphxqueue;
using namespace std;


int main(int argc, char **argv) {
    const int topic_id{1000};

    phxqueue::plugin::BreakPointFactory::SetBreakPointFactoryCreateFunc([]()->std::unique_ptr<phxqueue::plugin::BreakPointFactory> {
            return std::unique_ptr<phxqueue::plugin::BreakPointFactory>(new plugin::SKBreakPointFactory("./etc/client/global/skphxqueueoss.conf"));
        });

    phxqueue::comm::proto::AddRequest req;
    req.set_topic_id(topic_id);
    phxqueue::comm::StoreBaseMgrBP::GetThreadInstance()->OnAdd(req);
    return 0;
}


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

