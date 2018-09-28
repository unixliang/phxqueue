#include "skphxqueue/lock/sklock.h"

#include <cinttypes>

#include "iErrno.h"
#include "iLog.h"
#include "iOss.h"
#include "iSvrkit.h"

#include "phxpaxos/node.h"
#include "phxpaxos_skplugin/logger_sk.h"
#include "phxpaxos_skplugin/monitor_sk.h"


namespace skphxqueue {

namespace lock {


SKLock::SKLock(const phxqueue::lock::LockOption &opt) : phxqueue::lock::Lock(opt) {}

SKLock::~SKLock() {}

bool SKLock::NeedDropMaster(const int paxos_group_id) {
    auto opt(GetLockOption());

    const char *ip{opt->ip.c_str()};
    const int port{opt->port};

    Comm::ZKMgrClient *ptZKMgrClient{Comm::ZKMgrClient::GetDefault()};
    if (ptZKMgrClient && ptZKMgrClient->IsSvrBlocked(ip, port)) {
        MMIMPT("MASTERSTAT: svr(%s:%d) is globally blocked", ip, port);

        return true;
    }

    return false;
}

void SKLock::BeforeRunNode(phxpaxos::Options &opts) {
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
    monitor_conf.iOssAttrID = topic_config->GetProto().topic().lock_paxos_oss_attr_id();
    monitor_conf.iUseTimeOssAttrID = topic_config->GetProto().topic().lock_paxos_oss_attr_id_usetime();
    opts.poBreakpoint = phxpaxos::SKMonitor::GetBreakpoint(monitor_conf);
}


}  // namespace lock

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL: http://scm-gy.tencent.com/gzrd/gzrd_mail_rep/phoenix_proj/trunk/skphxqueue/src/lock/sklock.cpp $ $Id: sklock.cpp 2069181 2017-05-03 04:23:32Z walnuthe $ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

