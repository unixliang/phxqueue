#include "skphxqueue/test/test_skconfig.h"

#include <memory>

#include "skphxqueue/comm.h"
#include "skphxqueue/plugin.h"


namespace skphxqueue {

namespace test {


using namespace std;


void TestSKConfig::Process() {
    phxqueue::plugin::ConfigFactory::SetConfigFactoryCreateFunc([]()->unique_ptr<phxqueue::plugin::ConfigFactory> {
            return unique_ptr<plugin::SKConfigFactory>(new plugin::SKConfigFactory("./etc/client/global/skphxqueue.conf"));
        });

    const int topic_id{1000};

    // test topic_config
    {
        shared_ptr<const phxqueue::config::TopicConfig> topic_config;
        assert(phxqueue::comm::RetCode::RET_OK == phxqueue::config::GlobalConfig::GetThreadInstance()->GetTopicConfigByTopicID(topic_id, topic_config));
        assert(topic_config != nullptr);

        TestConfig::TestTopicConfig(topic_config.get());
    }

    // test consumer_config
    {
        shared_ptr<const phxqueue::config::ConsumerConfig> consumer_config;
        assert(phxqueue::comm::RetCode::RET_OK == phxqueue::config::GlobalConfig::GetThreadInstance()->GetConsumerConfig(topic_id, consumer_config));
        assert(consumer_config);

        TestConsumerConfig(consumer_config.get());
    }

    // test store_config
    {
        shared_ptr<const phxqueue::config::StoreConfig> store_config;
        assert(phxqueue::comm::RetCode::RET_OK == phxqueue::config::GlobalConfig::GetThreadInstance()->GetStoreConfig(topic_id, store_config));
        assert(store_config != nullptr);

        TestStoreConfig(store_config.get());
    }

    // test scheduler_config
    {
        shared_ptr<const phxqueue::config::SchedulerConfig> scheduler_config;
        assert(phxqueue::comm::RetCode::RET_OK == phxqueue::config::GlobalConfig::GetThreadInstance()->GetSchedulerConfig(topic_id, scheduler_config));
        assert(scheduler_config != nullptr);

        TestSchedulerConfig(scheduler_config.get());
    }

    // test lock_config
    {
        shared_ptr<const phxqueue::config::LockConfig> lock_config;
        assert(phxqueue::comm::RetCode::RET_OK == phxqueue::config::GlobalConfig::GetThreadInstance()->GetLockConfig(topic_id, lock_config));
        assert(lock_config != nullptr);

        TestLockConfig(lock_config.get());
    }
}


}  // namespace test

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

