#include "skphxqueue/scheduler/skscheduler.h"

#include <cinttypes>

#include "iErrno.h"
#include "iLog.h"
#include "iOss.h"
#include "iSvrkit.h"

#include "oss_call_stat_helper.h"
#include "mmlb_stat_helper.h"
#include "mmlbclient.h"


namespace skphxqueue {

namespace scheduler {


SKScheduler::SKScheduler(const phxqueue::scheduler::SchedulerOption &opt)
        : phxqueue::scheduler::Scheduler(opt) {}

SKScheduler::~SKScheduler() {}

bool SKScheduler::NeedDropMaster() {
    auto opt(GetSchedulerOption());

    const char *ip{opt->ip.c_str()};
    const int port{opt->port};

    Comm::ZKMgrClient *ptZKMgrClient{Comm::ZKMgrClient::GetDefault()};
    if (ptZKMgrClient && ptZKMgrClient->IsSvrBlocked(ip, port)) {
        MMIMPT("MASTERSTAT: svr(%s:%d) is globally blocked", ip, port);

        return true;
    }

    return false;
}

bool SKScheduler::NeedSkipUpdateLoad(const phxqueue::comm::proto::GetAddrScaleRequest &req) {
    const char *ip{req.addr().ip().c_str()};
    const int port{req.addr().port()};

    Comm::ZKMgrClient *ptZKMgrClient{Comm::ZKMgrClient::GetDefault()};
    if (ptZKMgrClient && ptZKMgrClient->IsSvrBlocked(ip, port)) {
        MMIMPT("skip consumer(%s:%d)", ip, port);

        return true;
    }

    return false;
}
void SKScheduler::OnKeepMasterThreadRun() {
    MMLBClient::SetRouteStatusReportCallback();
    oss_call_stat_dict_at(Comm::GetLogModuleName());
    oss_call_stat_dict_at("unknown");
    oss_call_stat_run(1, 1);
    mmlb_stat_run(1, 1);
    oss_call_stat_attach(0);
    mmlb_stat_attach(0);
}


}  // namespace scheduler

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL: http://scm-gy.tencent.com/gzrd/gzrd_mail_rep/phoenix_proj/trunk/skphxqueue/src/scheduler/skscheduler.cpp $ $Id: skscheduler.cpp 2069994 2017-05-03 09:37:19Z walnuthe $ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

