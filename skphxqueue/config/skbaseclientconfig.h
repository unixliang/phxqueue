#pragma once

#include <map>
#include <set>

#include "iFileFunc.h"

#include "phxqueue/comm.h"


namespace skphxqueue {

namespace config {


template <typename ConfigType> class SKBaseClientConfig
        : public Comm::CBaseClientConfig, public ConfigType {
  public:
    SKBaseClientConfig() {}
    virtual ~SKBaseClientConfig() {}

    /************************* ConfigType **********************/

    virtual phxqueue::comm::RetCode ReadConfig(typename ConfigType::ProtoType &proto) {
        return phxqueue::comm::RetCode::RET_OK;
    }

    virtual bool IsModified() {
        bool modified = false;
        Comm::CBaseClientConfig::LoadIfModified(modified);
        modified |= ConfigType::IsModified();
        return modified;
    }
};


}  // namespace config

}  // namespace skphxqueue

