#include "skphxqueue/test/sksimplehandler.h"

#include "iLog.h"


namespace skphxqueue {

namespace test {


phxqueue::comm::HandleResult
SKSimpleHandler::Handle(const phxqueue::comm::proto::ConsumerContext &cc,
                        phxqueue::comm::proto::QItem &item, string &uncompressed_buffer) {
    MMERR("INFO: uin %" PRIu64, (uint64_t)item.meta().uin());
    return phxqueue::comm::HandleResult::RES_OK;
}


}  // namespace test

}  // namespace phxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

