#include "skphxqueue/store/skstore.h"

#include <cinttypes>

#include "iErrno.h"
#include "iLog.h"
#include "iOss.h"
#include "iSvrkit.h"

#include "phxpaxos/node.h"
#include "phxpaxos_skplugin/logger_sk.h"
#include "phxpaxos_skplugin/monitor_sk.h"


namespace skphxqueue {

namespace store {


using namespace std;


SKStore::SKStore(const phxqueue::store::StoreOption &opt) : phxqueue::store::Store(opt) {}

SKStore::~SKStore() {}

bool SKStore::NeedDropMaster(const int paxos_group_id) {
    auto opt(GetStoreOption());

    const char *ip{opt->ip.c_str()};
    const int port{opt->port};

    Comm::ZKMgrClient *ptZKMgrClient{Comm::ZKMgrClient::GetDefault()};
    if (ptZKMgrClient && ptZKMgrClient->IsSvrBlocked(ip, port)) {
        MMIMPT("MASTERSTAT: svr(%s:%d) is globally blocked", ip, port);

        return true;
    }

    return false;
}


bool SKStore::IsStable() {
    auto cpu = phxqueue::comm::utils::GetCpu();
    if (cpu > 70) {
        MMERR("WARN: cpu %d > 70", cpu);
        return false;
    } else {
        MMERR("INFO: cpu %d", cpu);
    }

    MMERR("INFO: ok");

    return true;
}

void SKStore::BeforeRunNode(phxpaxos::Options &opts) {
    const int topic_id{GetTopicID()};

    phxqueue::comm::RetCode ret;

    shared_ptr<const phxqueue::config::TopicConfig> topic_config;
    ret = phxqueue::config::GlobalConfig::GetThreadInstance()->
            GetTopicConfigByTopicID(topic_id, topic_config);
    if (phxqueue::comm::RetCode::RET_OK != ret) {
        QLErr("GetTopicConfig ret %d topic_id %d", as_integer(ret), topic_id);
        return;
    }

    phxpaxos::MonitorConfig monitor_conf;
    monitor_conf.iOssAttrID = topic_config->GetProto().topic().store_paxos_oss_attr_id();
    monitor_conf.iUseTimeOssAttrID = topic_config->GetProto().topic().store_paxos_oss_attr_id_usetime();
    opts.poBreakpoint = phxpaxos::SKMonitor::GetBreakpoint(monitor_conf);
    opts.pLogFunc = phxpaxos::SKLogger::GetLogger();
}


}  // namespace store

}  // namespace phxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

