#pragma once

#include <memory>

#include "phxqueue/comm.h"
#include "phxqueue/plugin.h"


namespace skphxqueue {

namespace plugin {


class SKBreakPointFactory : public phxqueue::plugin::BreakPointFactory {
  public:
    SKBreakPointFactory(const std::string &oss_config_path);
    virtual ~SKBreakPointFactory();

    std::string GetOssFilePath();

    virtual std::unique_ptr<phxqueue::comm::ConsumerBP> NewConsumerBP();
    virtual std::unique_ptr<phxqueue::comm::ConsumerConsumeBP> NewConsumerConsumeBP();
    virtual std::unique_ptr<phxqueue::comm::ConsumerHeartBeatLockBP> NewConsumerHeartBeatLockBP();

    virtual std::unique_ptr<phxqueue::comm::StoreBP> NewStoreBP();
    virtual std::unique_ptr<phxqueue::comm::StoreBaseMgrBP> NewStoreBaseMgrBP();
    virtual std::unique_ptr<phxqueue::comm::StoreIMMasterBP> NewStoreIMMasterBP();
    virtual std::unique_ptr<phxqueue::comm::StoreSnatchMasterBP> NewStoreSnatchMasterBP();
    virtual std::unique_ptr<phxqueue::comm::StoreBacklogBP> NewStoreBacklogBP();

    virtual std::unique_ptr<phxqueue::comm::ProducerBP> NewProducerBP();
    virtual std::unique_ptr<phxqueue::comm::ProducerConsumerGroupBP> NewProducerConsumerGroupBP();

    virtual std::unique_ptr<phxqueue::comm::SchedulerBP> NewSchedulerBP();
    virtual std::unique_ptr<phxqueue::comm::SchedulerMgrBP> NewSchedulerMgrBP();
    virtual std::unique_ptr<phxqueue::comm::SchedulerLoadBalanceBP> NewSchedulerLoadBalanceBP();
    virtual std::unique_ptr<phxqueue::comm::SchedulerKeepMasterBP> NewSchedulerKeepMasterBP();

    virtual std::unique_ptr<phxqueue::comm::LockBP> NewLockBP();
    virtual std::unique_ptr<phxqueue::comm::LockMgrBP> NewLockMgrBP();
    virtual std::unique_ptr<phxqueue::comm::LockCleanThreadBP> NewLockCleanThreadBP();
    virtual std::unique_ptr<phxqueue::comm::LockIMMasterBP> NewLockIMMasterBP();
    virtual std::unique_ptr<phxqueue::comm::LockSnatchMasterBP> NewLockSnatchMasterBP();
    virtual std::unique_ptr<phxqueue::comm::LockSMBP> NewLockSMBP();

  private:
    class SKBreakPointFactoryImpl;
    std::unique_ptr<SKBreakPointFactoryImpl> impl_;
};


}  // namespace plugin

}  // namespace skphxqueue

