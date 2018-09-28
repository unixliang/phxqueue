#pragma once

#include "skphxqueue/config/skbaseconfig.h"

#include "phxqueue/config.h"


namespace skphxqueue {

namespace config {


class SKLockConfig : public SKBaseConfig<phxqueue::config::LockConfig> {
  public:
    SKLockConfig() : SKBaseConfig<phxqueue::config::LockConfig>() {}
    virtual ~SKLockConfig() {}

    virtual int Read(Comm::CConfig *conf, bool reload);
};


}  // namespace config

}  // namespace skphxqueue

