#pragma once

#include <map>
#include <set>

#include "iFileFunc.h"

#include "mmsection2pb.h"

#include "phxqueue/comm.h"


namespace skphxqueue {

namespace config {


template <typename ConfigType> class SKBaseConfig : public Comm::CBaseConfig, public ConfigType {
  public:
    SKBaseConfig() {}
    virtual ~SKBaseConfig() {}

    virtual int Read(Comm::CConfig *conf, bool /* reload */) {
        return 0;
    }

    virtual phxqueue::comm::RetCode ReadConfig(typename ConfigType::ProtoType &proto) {
        return phxqueue::comm::RetCode::RET_OK;
    }

    virtual bool IsModified() {
        bool modified = false;
        Comm::CBaseConfig::LoadIfModified(modified);
        modified |= ConfigType::IsModified();
        return modified;
    }
};

template <typename ConfigType> class SKBasePBConfig : public SKBaseConfig<ConfigType> {
  public:
    SKBasePBConfig() : SKBaseConfig<ConfigType>() {}
    virtual ~SKBasePBConfig() {}

    virtual int Read(Comm::CConfig *conf, bool /* reload */) {

        typename ConfigType::ProtoType proto;

        if (ConfigType::NeedCheck()) {
            mmsection2pb::ConfigSectionLoaderWithCheck section_loader(conf);
            mmsection2pb::ParseSection(&section_loader, &proto);
            assert(!section_loader.Error());
        } else {
            mmsection2pb::ConfigSectionLoader section_loader(conf);
            mmsection2pb::ParseSection(&section_loader, &proto);
        }

        ConfigType::FillConfig(move(proto));

        return 0;
    }
};


}  // namespace config

}  // namespace skphxqueue

