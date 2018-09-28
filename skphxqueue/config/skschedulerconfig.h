#pragma once

#include "phxqueue/config.h"

#include "skphxqueue/config/skbaseclientconfig.h"


namespace skphxqueue {

namespace config {


class SKSchedulerConfig : public SKBaseClientConfig<phxqueue::config::SchedulerConfig> {
  public:
    SKSchedulerConfig() : SKBaseClientConfig<phxqueue::config::SchedulerConfig>() {}
    virtual ~SKSchedulerConfig() {}

    virtual phxqueue::comm::RetCode ReadConfig(typename phxqueue::config::SchedulerConfig::ProtoType &proto);
};


}  // namespace config

}  // namespace skphxqueue

