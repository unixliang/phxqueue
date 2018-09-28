#include <cinttypes>
#include <iostream>
#include <sys/prctl.h>
#include <sys/wait.h>

#include "iLog.h"

#include "skphxqueue/config.h"
#include "skphxqueue/lock.h"
#include "skphxqueue/plugin.h"


using namespace skphxqueue;
using namespace std;


void LockRun(const int vpid) {
    phxqueue::comm::RetCode ret;

    auto proc_name(string("test_lock.") + to_string(vpid));

    Comm::OpenLog("test_skscheduler", 3, "/home/qspace/log");
    SetLogThreadMode(Comm::COMM_LOG_TM_ENABLE) ;

    phxqueue::config::LockConfig lock_config;
    lock_config.Load();

    vector<shared_ptr<const phxqueue::config::proto::Lock>> locks;
    if (phxqueue::comm::RetCode::RET_OK != (ret = lock_config.GetAllLock(locks))) {
        NLErr("GetAllLock ret %d", as_integer(ret));

        return;
    }
    if (0 == locks.size()) {
        NLErr("nr_lock 0");

        return;
    }
    if (3 != locks.at(0)->addrs_size()) {
        NLErr("locks[0]->nr_addr %zu != 3", locks[0]->addrs_size());

        return;
    }

    auto path_base(string("/tmp/phxqueue/lock.") + to_string(vpid));

    phxqueue::lock::LockOption opt;
    opt.topic = "test";
    opt.node_db_path = path_base + "/nodedb";
    opt.mirror_path = path_base + "/mirror";
    opt.ip = locks.at(0)->addrs(vpid).ip();
    opt.port = locks.at(0)->addrs(vpid).port();
    opt.paxos_port = locks.at(0)->addrs(vpid).paxos_port();
    opt.log_func = plugin::SKLogger::GetLogger();
    opt.nr_group = 2;

    NLVerb("lock %d opt done", vpid);

    phxqueue::lock::Lock lock(opt);
    if (phxqueue::comm::RetCode::RET_OK != (ret = lock.Init())) {
        NLErr("lock %d Init ret %d", vpid, as_integer(ret));

        return;
    }

    NLVerb("lock %d Init ret %d", vpid, as_integer(ret));

    sleep(1000);
}

int main(int argc, char **argv) {
    if (SIG_ERR == signal(SIGCHLD, SIG_IGN)) {
        perror("signal error");

        exit(EXIT_FAILURE);
    }

    for (int vpid{0}; vpid < 3; ++vpid) {
        pid_t pid = fork();
        if (pid == 0) {
            /* send SIGHUP to me if parent dies. */
            prctl(PR_SET_PDEATHSIG, SIGHUP);
            LockRun(vpid);
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
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL: http://scm-gy.tencent.com/gzrd/gzrd_mail_rep/phoenix_proj/trunk/skphxqueue/src/test/test_sklock_main.cpp $ $Id: test_sklock_main.cpp 2072345 2017-05-04 13:23:30Z walnuthe $ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

