#pragma once

#include <memory>

#include "phxqueue/plugin.h"


namespace skphxqueue {

namespace plugin {


class SKConfigFactory : public phxqueue::plugin::ConfigFactory {
  public:
    SKConfigFactory(const std::string &global_config_path);
    virtual ~SKConfigFactory();

    virtual std::unique_ptr<phxqueue::config::GlobalConfig> NewGlobalConfig();
    virtual std::unique_ptr<phxqueue::config::TopicConfig> NewTopicConfig(const int topic_id, const std::string &path);
    virtual std::unique_ptr<phxqueue::config::ConsumerConfig> NewConsumerConfig(const int topic_id, const std::string &path);
    virtual std::unique_ptr<phxqueue::config::StoreConfig> NewStoreConfig(const int topic_id, const std::string &path);
    virtual std::unique_ptr<phxqueue::config::SchedulerConfig> NewSchedulerConfig(const int topic_id, const std::string &path);
    virtual std::unique_ptr<phxqueue::config::LockConfig> NewLockConfig(const int topic_id, const std::string &path);

  public:
    void SetNeedCheck(bool need_check);
	bool IsNeedCheck();

  private:
    class SKConfigFactoryImpl;
	std::unique_ptr<SKConfigFactoryImpl> impl_;
};


}  // namespace plugin

}  // namespace skphxqueue

