#include "skphxqueue/plugin/skconfigfactory.h"

#include "iLog.h"

#include "skphxqueue/config.h"


namespace skphxqueue {

namespace plugin {


using namespace std;

class SKConfigFactory::SKConfigFactoryImpl {
	public:
		SKConfigFactoryImpl() {}
		virtual ~SKConfigFactoryImpl() {}

		std::string global_config_path;
		bool need_check = false;
};

SKConfigFactory::SKConfigFactory(const string &global_config_path)
        : phxqueue::plugin::ConfigFactory(), impl_(new SKConfigFactoryImpl()) {
    impl_->global_config_path = global_config_path;
}

SKConfigFactory::~SKConfigFactory() {}

unique_ptr<phxqueue::config::GlobalConfig> SKConfigFactory::NewGlobalConfig() {
    MMDEBUG("path %s", impl_->global_config_path.c_str());

    auto &&conf = new config::SKGlobalConfig();
    conf->SetNeedCheck(impl_->need_check);
    conf->SetFileIfUnset(impl_->global_config_path.c_str());
    if (conf) conf->Load();

    return unique_ptr<config::SKGlobalConfig>(conf);
}

unique_ptr<phxqueue::config::TopicConfig> SKConfigFactory::NewTopicConfig(const int topic_id, const string &path) {
    MMDEBUG("topic_id %d path %s", topic_id, path.c_str());

    auto &&conf = new config::SKTopicConfig();
    conf->SetNeedCheck(impl_->need_check);
    conf->SetFileIfUnset(path.c_str());
    if (conf) conf->Load();

    return unique_ptr<config::SKTopicConfig>(conf);
}

unique_ptr<phxqueue::config::ConsumerConfig> SKConfigFactory::NewConsumerConfig(const int topic_id, const string &path) {
    MMDEBUG("topic_id %d path %s", topic_id, path.c_str());

    auto &&conf = new config::SKConsumerConfig();
    conf->SetNeedCheck(impl_->need_check);
    conf->SetFileIfUnset(path.c_str());
    if (conf) conf->Load();

    return unique_ptr<config::SKConsumerConfig>(conf);
}

unique_ptr<phxqueue::config::StoreConfig> SKConfigFactory::NewStoreConfig(const int topic_id, const string &path) {
    MMDEBUG("topic_id %d path %s", topic_id, path.c_str());

    auto &&conf = new config::SKStoreConfig();
    conf->SetNeedCheck(impl_->need_check);
    conf->SetFileIfUnset(path.c_str());
    if (conf) conf->Load();

    return unique_ptr<config::SKStoreConfig>(conf);
}

unique_ptr<phxqueue::config::SchedulerConfig> SKConfigFactory::NewSchedulerConfig(const int topic_id, const string &path) {
    MMDEBUG("topic_id %d path %s", topic_id, path.c_str());

    auto &&conf = new config::SKSchedulerConfig();
    conf->SetNeedCheck(impl_->need_check);
    conf->SetFileIfUnset(path.c_str());
    if (conf) conf->Load();

    return unique_ptr<config::SKSchedulerConfig>(conf);
}

unique_ptr<phxqueue::config::LockConfig> SKConfigFactory::NewLockConfig(const int topic_id, const string &path) {
    MMDEBUG("topic_id %d path %s", topic_id, path.c_str());

    auto &&conf = new config::SKLockConfig();
    conf->SetNeedCheck(impl_->need_check);
    conf->SetFileIfUnset(path.c_str());
    if (conf) conf->Load();

    return unique_ptr<config::SKLockConfig>(conf);
}


void SKConfigFactory::SetNeedCheck(bool need_check) {
    impl_->need_check = need_check;
}

bool SKConfigFactory::IsNeedCheck() {
	return impl_->need_check;
}




}  // namespace plugin

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

