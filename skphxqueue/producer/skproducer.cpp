#include "skphxqueue/producer/skproducer.h"

#include "iLog.h"

#include "skbuffer.h"
#include "skfrmwcookie.h"
#include "snappy.h"

#include "phxqueue/comm.h"

#include "skphxqueue/producer/skselector.h"


namespace skphxqueue {

namespace producer {


using namespace std;


void SKProducer::SetUserCookies(phxqueue::comm::proto::Cookies &user_cookie) {
    OssAttrInc(59104, 0, 1);

    skphxqueue::comm::utils::PrintCallGraphInfo();

    // dyeloginfo
    {
        OssAttrInc(59104, 1, 1);
        Comm::SKBuffer cookie_buf;
        Comm::DyeLogInfo_t dyeLogInfo;
        Comm::GetDyeLogInfo(&dyeLogInfo);

        MMDEBUG("writebroker dyeloginfo graph_node_id %d", dyeLogInfo.graphNodeID);

        if (!Comm::SKFrmwCookie::DyeLogInfoToBuffer(dyeLogInfo, &cookie_buf)) {
            auto &&cookie = user_cookie.add_cookies();
            cookie->set_key("dyeloginfo");
            cookie->set_val((const char *)cookie_buf.GetBuffer(), cookie_buf.GetLen());
            OssAttrInc(59104, 2, 1);
        } else {
            OssAttrInc(59104, 3, 1);
        }
    }

    // syscookie
    {
        OssAttrInc(59104, 4, 1);
        Comm::MMSystemReqCookie * syscookie = Comm::GetSysReqCookie();

        MMDEBUG("writebroker syscookie graph_node_id %d", syscookie->graph_node_id());

        std::string cookie_buf;
        if (syscookie->SerializeToString(&cookie_buf)) {
            auto &&cookie = user_cookie.add_cookies();
            cookie->set_key("syscookie");
            cookie->set_val(cookie_buf);
            OssAttrInc(59104, 5, 1);
        } else {
            OssAttrInc(59104, 6, 1);
        }
    }
}

void SKProducer::CompressBuffer(const string &buffer,
                                string &compressed_buffer, int &buffer_type) {
    snappy::Compress(buffer.c_str(), buffer.length(), &compressed_buffer);
    buffer_type = 1;
}

unique_ptr<phxqueue::producer::StoreSelector>
SKProducer::NewStoreSelector(const int topic_id, const int pub_id,
                             const uint64_t uin, const bool retry_switch_store) {
    return unique_ptr<SKStoreSelectorDefault>
            (new SKStoreSelectorDefault(topic_id, pub_id, uin, retry_switch_store));
}


}  // namespace producer

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

