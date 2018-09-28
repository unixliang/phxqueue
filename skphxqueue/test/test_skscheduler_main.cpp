#include <cinttypes>
#include <iostream>
#include <sys/prctl.h>
#include <sys/wait.h>

#include "iLog.h"

#include "phxqueue/config.h"

#include "skphxqueue/plugin.h"
#include "skphxqueue/test/sksimplescheduler.h"


using namespace skphxqueue;
using namespace std;


void SchedulerRun(const int vpid) {
    phxqueue::comm::RetCode ret;

    auto proc_name(string("test_scheduler.") + to_string(vpid));

    Comm::OpenLog("test_skscheduler", 3, "/home/qspace/log");
    SetLogThreadMode(Comm::COMM_LOG_TM_ENABLE) ;

    phxqueue::config::SchedulerConfig scheduler_config;
    scheduler_config.Load();

    shared_ptr<const phxqueue::config::proto::Scheduler> template_scheduler;
    if (phxqueue::comm::RetCode::RET_OK != (ret = scheduler_config.GetScheduler(template_scheduler))) {
        NLErr("GetAllScheduler ret %d", as_integer(ret));

        return;
    }
    if (3 != template_scheduler->addrs_size()) {
        NLErr("scheduler->nr_addr %zu != 3", template_scheduler->addrs_size());

        return;
    }

    auto path_base(string("/tmp/phxqueue/scheduler.") + to_string(vpid));

    phxqueue::scheduler::SchedulerOption opt;
    opt.ip = template_scheduler->addrs(vpid).ip();
    opt.port = template_scheduler->addrs(vpid).port();

    opt.log_func = plugin::SKLogger::GetLogger();

    NLVerb("scheduler %d opt done", vpid);

    test::SKSimpleScheduler sk_simple_scheduler(opt);
    if (phxqueue::comm::RetCode::RET_OK != (ret = sk_simple_scheduler.Init())) {
        NLErr("scheduler %d Init ret %d", vpid, as_integer(ret));

        return;
    }

    NLVerb("scheduler %d Init ret %d", vpid, phxqueue::comm::as_integer(ret));

    sleep(1000);
}

int main(int argc, char **argv) {
    if (SIG_ERR == signal(SIGCHLD, SIG_IGN)) {
        perror("signal error");

        exit(EXIT_FAILURE);
    }

    for (int vpid{0}; vpid < 3; ++vpid) {
        pid_t pid{fork()};
        if (0 == pid) {
            /* send SIGHUP to me if parent dies. */
            prctl(PR_SET_PDEATHSIG, SIGHUP);
            SchedulerRun(vpid);
            exit(0);
        }
    }

    sleep(1000);

    return 0;
}


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL: http://scm-gy.tencent.com/gzrd/gzrd_mail_rep/phoenix_proj/trunk/skphxqueue/src/test/test_skscheduler_main.cpp $ $Id: test_skscheduler_main.cpp 2072345 2017-05-04 13:23:30Z walnuthe $ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

