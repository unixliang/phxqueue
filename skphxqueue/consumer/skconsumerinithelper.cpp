#include "skphxqueue/consumer/skconsumerinithelper.h"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <errno.h>

#include "iFileFunc.h"
#include "iLog.h"
#include "iSvrkit.h"

#include "skroutereporthelper.h"

#include "skphxqueue/consumer/skconsumerserverconfig.h"
#include "skphxqueue/consumer/skconsumercallgraphhelper.h"
#include "skphxqueue/plugin.h"


extern char *program_invocation_short_name;


namespace skphxqueue {

namespace consumer {


using namespace Comm;


void SKConsumerInitHelperBase::Init(int argc, char *argv[], phxqueue::consumer::ConsumerOption &opt) {
    const char *modulename = program_invocation_short_name;

    int ret = mmlas::InitForClient();
    MMERR("INFO: mmlas::InitForClient ret %d", ret);

    Comm::OpenLog(modulename, 3, "/home/qspace/log");
    SetLogThreadMode(Comm::COMM_LOG_TM_ENABLE);


    char confpath[256] = {0};
    int daemon{0};
    memset(confpath, 0, sizeof(confpath));

    if (0 != SKEpollUtils::CommandLine(argc, argv, modulename, &daemon, confpath, sizeof(confpath) - 1)) {
        LogErr("ERR: Parse CommandLine failed");
        exit(-1);
    }

    MMERR("INFO: configpath %s", confpath);

    if (daemon) {
        SKEpollUtils::ForkAsDaemon();
    }

    SKConsumerServerConfig conf;
    if (0 != conf.ReadConfig(confpath)) {
        MMIMPT("ERR: ReadConfig failed");
        exit(-1);
    }

    OpenLog(modulename, conf.GetLogLevel(), "/home/qspace/log");

    opt.topic = conf.GetTopic();
    opt.ip = conf.GetEpollConfig()->GetSvrIP();
    opt.port = conf.GetEpollConfig()->GetSvrPort();
    opt.paxos_port = 0;
    opt.nprocs = conf.GetNProcs();
    opt.shm_key_base = conf.GetShmKeyBase();
    opt.proc_pid_path = string("/tmp/") + string(modulename);
    opt.lock_path_base = string("/") + string(modulename) + string(".lock.");
    opt.log_func = plugin::SKLogger::GetLogger();

    global_config_path_ = conf.GetPhxQueueGlobalConfigPath();
    oss_config_path_ = conf.GetPhxQueueOssConfigPath();


    // call graph
    {
        const auto ossid = conf.GetEpollConfig()->GetOssAttrID();
        SKConsumerCallGraphHelper::GetInstance()->Init(ossid);
        MMERR("Init ossid %d", ossid);
    }

    // route oss
    {
        pid_t pid = fork();
        if (0 == pid) {
            MMERR("INFO: run RouteInfoReportThread. path %s", confpath);
            RouteInfoReportThread((void*)confpath);
            exit(0);
        } else if (0 > pid) exit(-1);
    }

}


}  // namespace consumer

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

