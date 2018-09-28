#pragma once

#include "phxqueue/config.h"

#include "skphxqueue/config/skbaseconfig.h"


namespace skphxqueue {

namespace config {


class SKStoreConfig : public SKBaseConfig<phxqueue::config::StoreConfig> {
  public:
    SKStoreConfig() : SKBaseConfig<phxqueue::config::StoreConfig>() {}
    virtual ~SKStoreConfig() {}

    virtual int Read(Comm::CConfig *conf, bool reload);
};


}  // namespace config

}  // namespace skphxqueue

