#pragma once

#include <cstdint>
#include <memory>

#include "phxqueue/producer.h"


namespace skphxqueue {

namespace producer {


class SKStoreSelectorDefault : public phxqueue::producer::StoreSelectorDefault {
  public:
    SKStoreSelectorDefault(const int topic_id, const int pub_id, const uint64_t uin,
                           const bool retry_switch_store = false);
    virtual ~SKStoreSelectorDefault();

  private:
    virtual bool IsStoreBlocked(const int store_id);
};


}  // namespace producer

}  // namespace skphxqueue

