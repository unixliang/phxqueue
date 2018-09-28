#pragma once

#include "phxqueue/config.h"

#include "skphxqueue/config/skbaseconfig.h"


namespace skphxqueue {

namespace config {


class SKTopicConfig : public SKBasePBConfig<phxqueue::config::TopicConfig> {
  public:
    SKTopicConfig() : SKBasePBConfig<phxqueue::config::TopicConfig>() {}
    virtual ~SKTopicConfig() {}
};


}  // namespace config

}  // namespace skphxqueue

