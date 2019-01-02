#include "skphxqueue/producer/skselector.h"

#include <functional>
#include <memory>

#include <zlib.h>

#include "iCrypto.h"
#include "iLog.h"
#include "iSvrkit.h"

#include "phxqueue/config.h"


namespace skphxqueue {

namespace producer {


using namespace std;


SKStoreSelectorDefault::SKStoreSelectorDefault(const int topic_id, const int pub_id, const uint64_t uin, const bool retry_switch_store)
    : phxqueue::producer::StoreSelectorDefault(topic_id, pub_id, uin, retry_switch_store)
{}


SKStoreSelectorDefault::~SKStoreSelectorDefault() {}

bool SKStoreSelectorDefault::IsStoreBlocked(const int store_id) {
    phxqueue::comm::RetCode ret;

    auto ptZKMgrClient = Comm::ZKMgrClient::GetDefault();
    if (!ptZKMgrClient) return false;
    unsigned int dyeuin = Comm::GetDyeLogUin();
    
    OssAttrInc(64737, 0, 1);
    OssAttrInc(64737, 1, 1);

    const int topic_id = GetTopicID();

    shared_ptr<const phxqueue::config::StoreConfig> store_config;
    if (phxqueue::comm::RetCode::RET_OK != (ret = phxqueue::config::GlobalConfig::GetThreadInstance()->GetStoreConfig(topic_id, store_config))) {
        MMERR("ERR: GetStoreConfig ret %d", as_integer(ret));
        return false;
    }

    shared_ptr<const phxqueue::config::proto::Store> store;
    if (phxqueue::comm::RetCode::RET_OK != (ret = store_config->GetStoreByStoreID(store_id, store))) {
        MMERR("ERR: GetStoreByStoreID ret %d store_id %d", as_integer(ret), store_id);
        return true;
    }

    int nblock_global = 0;

    for (size_t i = 0; i < store->addrs_size(); ++i) {
        auto &&addr = store->addrs(i);

        OssAttrInc(64737, 2, 1);

        const char *ip = addr.ip().c_str();
        const int port = addr.port();

        if (ptZKMgrClient->IsSvrBlocked(ip, port)) {
            ++nblock_global;
            OssAttrInc(64737, 4, 1);
            MMERR("ERR: addr(%s:%d) is globally blocked", ip, port);
            continue;
        } else {
            OssAttrInc(64737, 5, 1);
        }
    }
    if (nblock_global >= (store->addrs_size() / 2 + 1)) {
        return true;
    }
    // ok
    OssAttrInc(64737, 6, 1);
    return false;
}

bool SKStoreSelectorDefault::IsStorePercentBlocked(const int store_id) {
    phxqueue::comm::RetCode ret;

    auto ptZKMgrClient = Comm::ZKMgrClient::GetDefault();
    if (!ptZKMgrClient) return false;
    unsigned int dyeuin = Comm::GetDyeLogUin();
    
    OssAttrInc(114904, 0, 1);
    OssAttrInc(114904, 1, 1);

    const int topic_id = GetTopicID();

    shared_ptr<const phxqueue::config::StoreConfig> store_config;
    if (phxqueue::comm::RetCode::RET_OK != (ret = phxqueue::config::GlobalConfig::GetThreadInstance()->GetStoreConfig(topic_id, store_config))) {
        MMERR("ERR: GetStoreConfig ret %d", as_integer(ret));
        return false;
    }

    shared_ptr<const phxqueue::config::proto::Store> store;
    if (phxqueue::comm::RetCode::RET_OK != (ret = store_config->GetStoreByStoreID(store_id, store))) {
        MMERR("ERR: GetStoreByStoreID ret %d store_id %d", as_integer(ret), store_id);
        return true;
    }

    if (0 == store->addrs_size()) {
        MMERR("ERR: store->addrs_size %d invalid", store->addrs_size());
        return false;
    }

    int nblock_percent = 0;

    // only check first ip
    {
        auto &&addr = store->addrs(0);

        OssAttrInc(114904, 2, 1);

        const char *ip = addr.ip().c_str();
        const int port = addr.port();

        if (Comm::IsPercentBlocked(ip, port, dyeuin)) {
            ++nblock_percent;
            OssAttrInc(114904, 24, 1);
            MMERR("ERR: addr(%s:%d) is percent blocked", ip, port);
        } else {
            OssAttrInc(114904, 25, 1);
        }
    }
    if (nblock_percent) {
        return true;
    }
    // ok
    OssAttrInc(114904, 6, 1);
    return false;
}

}  // namespace producer

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

