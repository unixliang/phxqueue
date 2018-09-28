#pragma once

#include "skphxqueue/config/skbaseconfig.h"
#include "phxqueue/config.h"


namespace skphxqueue {

namespace config {


class SKGlobalConfig : public SKBasePBConfig<phxqueue::config::GlobalConfig> {
  public:
    SKGlobalConfig() : SKBasePBConfig<phxqueue::config::GlobalConfig>() {}
    virtual ~SKGlobalConfig() {}
};


}  // namespace config

}  // namespace skphxqueue

