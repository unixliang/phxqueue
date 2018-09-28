#pragma once

#include "phxqueue/consumer.h"
#include "phxqueue/plugin.h"


namespace skphxqueue {

namespace consumer {


class SKConsumerInitHelperBase {
  public:
    void Init(int argc, char *argv[], phxqueue::consumer::ConsumerOption &opt);

  protected:
    std::string global_config_path_ = "";
    std::string oss_config_path_ = "";
};

template <typename ConfigFactoryType, typename BreakPointFactoryType>
class SKConsumerInitHelper : public SKConsumerInitHelperBase {
  public:
    void Init(int argc, char *argv[], phxqueue::consumer::ConsumerOption &opt) {
        SKConsumerInitHelperBase::Init(argc, argv, opt);

        if (!global_config_path_.empty()) {
            opt.config_factory_create_func = [this]()->std::unique_ptr<phxqueue::plugin::ConfigFactory> {
                return std::unique_ptr<phxqueue::plugin::ConfigFactory>(new ConfigFactoryType(global_config_path_));
            };
        }

        if (!oss_config_path_.empty()) {
            opt.break_point_factory_create_func = [this]()->std::unique_ptr<phxqueue::plugin::BreakPointFactory> {
                return std::unique_ptr<phxqueue::plugin::BreakPointFactory>(new BreakPointFactoryType(oss_config_path_));
            };
        }
    }
};


}  // namespace consumer

}  // namespace skphxqueue

