#include "skphxqueue/test/sksimpleconsumer.h"

#include <iostream>
#include <unistd.h>

#include "iLog.h"

#include "skphxqueue/config.h"


namespace skphxqueue {

namespace test {


using namespace std;


phxqueue::comm::RetCode
        SKSimpleConsumer::Get(const phxqueue::comm::proto::GetRequest &req,
                              phxqueue::comm::proto::GetResponse &resp) {
    MMERR("INFO: Get topic_id %d store_id %d queue_id %d pub_id %d",
          req.topic_id(), req.store_id(), req.queue_id(), req.pub_id());

    phxqueue::comm::proto::QItem item;
    phxqueue::comm::proto::Meta &meta = *item.mutable_meta();

    meta.set_topic_id(1000);
    meta.set_handle_id(1);

    resp.set_prev_cursor_id(1);
    resp.set_next_cursor_id(1);
    resp.add_items()->CopyFrom(item);

    return phxqueue::comm::RetCode::RET_OK;
}

phxqueue::comm::RetCode
SKSimpleConsumer::GetAddrScale(const phxqueue::comm::proto::GetAddrScaleRequest &req,
                               phxqueue::comm::proto::GetAddrScaleResponse &resp) {
    // return default
    phxqueue::comm::RetCode ret;

    shared_ptr<const phxqueue::config::ConsumerConfig> consumer_config;
    if (phxqueue::comm::RetCode::RET_OK !=
        (ret = phxqueue::config::GlobalConfig::GetThreadInstance()->GetConsumerConfig(GetTopicID(), consumer_config))) {
        MMERR("ERR: GetConsumerConfig ret %d", as_integer(ret));
        return ret;
    }

    for (size_t i{0}; i < consumer_config->GetProto().consumers_size(); ++i) {
        auto &&consumer = consumer_config->GetProto().consumers(i);
        auto &&addr_scale = resp.add_addr_scales();
        addr_scale->mutable_addr()->CopyFrom(consumer.addr());
        addr_scale->set_scale(consumer.scale());
    }

    return phxqueue::comm::RetCode::RET_OK;
}

phxqueue::comm::RetCode
SKSimpleConsumer::GetLockInfo(const phxqueue::comm::proto::GetLockInfoRequest &req,
                              phxqueue::comm::proto::GetLockInfoResponse &resp) {
    return phxqueue::comm::RetCode::RET_ERR_NO_IMPL;
}

phxqueue::comm::RetCode
SKSimpleConsumer::AcquireLock(const phxqueue::comm::proto::AcquireLockRequest &req,
                              phxqueue::comm::proto::AcquireLockResponse &resp) {
    return phxqueue::comm::RetCode::RET_ERR_NO_IMPL;
}

void SKSimpleConsumer::BeforeLock(const phxqueue::comm::proto::ConsumerContext &cc) {
    MMINFO("INFO: BeforeLock cc consumer_group_id %d pub_id %d store_id %d queue_id %d",
           cc.consumer_group_id(), cc.pub_id(), cc.store_id(), cc.queue_id());
}

void SKSimpleConsumer::AfterLock(const phxqueue::comm::proto::ConsumerContext &cc) {
    MMINFO("INFO: AfterLock cc consumer_group_id %d pub_id %d store_id %d queue_id %d",
           cc.consumer_group_id(), cc.pub_id(), cc.store_id(), cc.queue_id());
}


}  // namespace test

}  // namespace phxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

