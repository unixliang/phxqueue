#include <iostream>

#include "iLog.h"

#include "skphxqueue/comm.h"
#include "skphxqueue/consumer.h"
#include "skphxqueue/plugin.h"
#include "skphxqueue/test/sksimpleconsumer.h"
#include "skphxqueue/test/sksimplehandler.h"


using namespace skphxqueue;
using namespace std;


int main(int argc, char **argv) {
    Comm::OpenLog("test_skconsumer", 3, "/home/qspace/log");
    SetLogThreadMode(Comm::COMM_LOG_TM_ENABLE) ;

    phxqueue::consumer::ConsumerOption opt;
    opt.topic = "test";
    opt.ip = "10.0.1.1";
    opt.nprocs = 3;
    opt.proc_pid_path = "/tmp/phxqueue/";
    opt.lock_path_base = "./phxqueueconsumer.lock.";
    opt.log_func = plugin::SKLogger::GetLogger();

    test::SKSimpleConsumer consumer(opt);
    consumer.AddHandlerFactory(1, new phxqueue::comm::DefaultHandlerFactory<test::SKSimpleHandler>());
    consumer.Run();

    return 0;
}


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

