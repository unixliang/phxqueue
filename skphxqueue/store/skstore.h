#pragma once

#include "phxqueue/store.h"


namespace skphxqueue {

namespace store {


class SKStore : public phxqueue::store::Store {
  public:
    SKStore(const phxqueue::store::StoreOption &opt);
    virtual ~SKStore() override;


    virtual bool NeedDropMaster(const int paxos_group_id) override;

    virtual bool IsStable();

  private:
    virtual void BeforeRunNode(phxpaxos::Options &opts) override;
};


}  // namespace store

}  // namespace skphxqueue

