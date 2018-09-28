#pragma once

#include "skphxqueue/config/skbaseclientconfig.h"

#include "phxqueue/config.h"


namespace skphxqueue {

namespace config {


class SKConsumerConfig : public SKBaseClientConfig<phxqueue::config::ConsumerConfig> {
  public:
    SKConsumerConfig() : SKBaseClientConfig<phxqueue::config::ConsumerConfig>() {}
    virtual ~SKConsumerConfig() {}

    virtual phxqueue::comm::RetCode ReadConfig(typename phxqueue::config::ConsumerConfig::ProtoType &proto);

    virtual void FillConsumerGroupIDs(phxqueue::config::proto::Consumer &consumer);
};


}  // namespace config

}  // namespace skphxqueue

