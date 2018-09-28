#pragma once

#include "phxqueue/comm.h"
#include "phxqueue/scheduler.h"


namespace skphxqueue {

namespace scheduler {


class SKScheduler : public phxqueue::scheduler::Scheduler {
  public:
    SKScheduler(const phxqueue::scheduler::SchedulerOption &opt);
    virtual ~SKScheduler() override;

    virtual bool NeedDropMaster() override;

    virtual bool NeedSkipUpdateLoad(const phxqueue::comm::proto::GetAddrScaleRequest &req) override;

    virtual void OnKeepMasterThreadRun() override;

};


}  // namespace scheduler

}  // namespace skphxqueue

