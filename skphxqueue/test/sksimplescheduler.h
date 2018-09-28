#pragma once

#include <memory>

#include "skphxqueue/scheduler.h"


namespace skphxqueue {

namespace test {

class SKSimpleScheduler : public scheduler::SKScheduler {
  public:
    SKSimpleScheduler(const phxqueue::scheduler::SchedulerOption &opt) : scheduler::SKScheduler(opt) {}
    virtual ~SKSimpleScheduler() {}

  protected:
    virtual phxqueue::comm::RetCode
    GetLockInfo(const phxqueue::comm::proto::GetLockInfoRequest &req,
                phxqueue::comm::proto::GetLockInfoResponse &resp) override;
    virtual phxqueue::comm::RetCode
    AcquireLock(const phxqueue::comm::proto::AcquireLockRequest &req,
                phxqueue::comm::proto::AcquireLockResponse &resp) override;
};


}  // namespace test

}  // namespace skphxqueue

