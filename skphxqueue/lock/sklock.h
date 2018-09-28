#pragma once

#include "phxqueue/lock.h"


namespace skphxqueue {

namespace lock {


class SKLock : public phxqueue::lock::Lock {
  public:
    SKLock(const phxqueue::lock::LockOption &opt);
    virtual ~SKLock() override;

    virtual bool NeedDropMaster(const int paxos_group_id) override;

  private:
    virtual void BeforeRunNode(phxpaxos::Options &opts) override;
};


}  // namespace lock

}  // namespace skphxqueue

