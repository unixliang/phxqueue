#include "skphxqueue/plugin/skbreakpointfactory.h"

#include <string>

#include "phxqueue/comm.h"

#include "skphxqueue/comm.h"


namespace skphxqueue {

namespace plugin {


using namespace std;


class SKBreakPointFactory::SKBreakPointFactoryImpl {
  public:
    SKBreakPointFactoryImpl() {}
    virtual ~SKBreakPointFactoryImpl() {}

    string oss_file_path;
};

SKBreakPointFactory::SKBreakPointFactory(const string &oss_file_path) : BreakPointFactory(), impl_(new SKBreakPointFactoryImpl()) {
    impl_->oss_file_path = oss_file_path;
}

SKBreakPointFactory::~SKBreakPointFactory() {
}

string SKBreakPointFactory::GetOssFilePath() {
    return impl_->oss_file_path;
}

unique_ptr<phxqueue::comm::ConsumerBP> SKBreakPointFactory::NewConsumerBP() {
    return unique_ptr<comm::SKConsumerBP>(new comm::SKConsumerBP());
}

unique_ptr<phxqueue::comm::ConsumerConsumeBP> SKBreakPointFactory::NewConsumerConsumeBP() {
    return unique_ptr<comm::SKConsumerConsumeBP>(new comm::SKConsumerConsumeBP());
}

unique_ptr<phxqueue::comm::ConsumerHeartBeatLockBP> SKBreakPointFactory::NewConsumerHeartBeatLockBP() {
    return unique_ptr<comm::SKConsumerHeartBeatLockBP>(new comm::SKConsumerHeartBeatLockBP());
}

unique_ptr<phxqueue::comm::StoreBP> SKBreakPointFactory::NewStoreBP() {
    return unique_ptr<comm::SKStoreBP>(new comm::SKStoreBP());
}

unique_ptr<phxqueue::comm::StoreBaseMgrBP> SKBreakPointFactory::NewStoreBaseMgrBP() {
    return unique_ptr<comm::SKStoreBaseMgrBP>(new comm::SKStoreBaseMgrBP());
}

unique_ptr<phxqueue::comm::StoreIMMasterBP> SKBreakPointFactory::NewStoreIMMasterBP() {
    return unique_ptr<comm::SKStoreIMMasterBP>(new comm::SKStoreIMMasterBP());
}

unique_ptr<phxqueue::comm::StoreSnatchMasterBP> SKBreakPointFactory::NewStoreSnatchMasterBP() {
    return unique_ptr<comm::SKStoreSnatchMasterBP>(new comm::SKStoreSnatchMasterBP());
}

unique_ptr<phxqueue::comm::StoreBacklogBP> SKBreakPointFactory::NewStoreBacklogBP() {
    return unique_ptr<comm::SKStoreBacklogBP>(new comm::SKStoreBacklogBP());
}

unique_ptr<phxqueue::comm::ProducerBP> SKBreakPointFactory::NewProducerBP() {
    return unique_ptr<comm::SKProducerBP>(new comm::SKProducerBP());
}

unique_ptr<phxqueue::comm::ProducerConsumerGroupBP> SKBreakPointFactory::NewProducerConsumerGroupBP() {
    return unique_ptr<comm::SKProducerConsumerGroupBP>(new comm::SKProducerConsumerGroupBP());
}


unique_ptr<phxqueue::comm::SchedulerBP> SKBreakPointFactory::NewSchedulerBP() {
    return unique_ptr<comm::SKSchedulerBP>(new comm::SKSchedulerBP());
}


unique_ptr<phxqueue::comm::SchedulerMgrBP> SKBreakPointFactory::NewSchedulerMgrBP() {
    return unique_ptr<comm::SKSchedulerMgrBP>(new comm::SKSchedulerMgrBP());
}

unique_ptr<phxqueue::comm::SchedulerLoadBalanceBP> SKBreakPointFactory::NewSchedulerLoadBalanceBP() {
    return unique_ptr<comm::SKSchedulerLoadBalanceBP>(new comm::SKSchedulerLoadBalanceBP());
}

unique_ptr<phxqueue::comm::SchedulerKeepMasterBP> SKBreakPointFactory::NewSchedulerKeepMasterBP() {
    return unique_ptr<comm::SKSchedulerKeepMasterBP>(new comm::SKSchedulerKeepMasterBP());
}

unique_ptr<phxqueue::comm::LockBP> SKBreakPointFactory::NewLockBP() {
    return unique_ptr<comm::SKLockBP>(new comm::SKLockBP());
}


unique_ptr<phxqueue::comm::LockMgrBP> SKBreakPointFactory::NewLockMgrBP() {
    return unique_ptr<comm::SKLockMgrBP>(new comm::SKLockMgrBP());
}


unique_ptr<phxqueue::comm::LockCleanThreadBP> SKBreakPointFactory::NewLockCleanThreadBP() {
    return unique_ptr<comm::SKLockCleanThreadBP>(new comm::SKLockCleanThreadBP());
}


unique_ptr<phxqueue::comm::LockIMMasterBP> SKBreakPointFactory::NewLockIMMasterBP() {
    return unique_ptr<comm::SKLockIMMasterBP>(new comm::SKLockIMMasterBP());
}


unique_ptr<phxqueue::comm::LockSnatchMasterBP> SKBreakPointFactory::NewLockSnatchMasterBP() {
    return unique_ptr<comm::SKLockSnatchMasterBP>(new comm::SKLockSnatchMasterBP());
}

unique_ptr<phxqueue::comm::LockSMBP> SKBreakPointFactory::NewLockSMBP() {
    return unique_ptr<comm::SKLockSMBP>(new comm::SKLockSMBP());
}


}  // namespace plugin

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

