#pragma once

#include <memory>

#include "skphxqueue/consumer.h"


namespace skphxqueue {

namespace test {


class SKSimpleConsumer : public consumer::SKConsumer {
  public:
    SKSimpleConsumer(const phxqueue::consumer::ConsumerOption &opt) : consumer::SKConsumer(opt) {}
    virtual ~SKSimpleConsumer() {}

    virtual phxqueue::comm::RetCode
    Get(const phxqueue::comm::proto::GetRequest &req, phxqueue::comm::proto::GetResponse &resp);
    virtual phxqueue::comm::RetCode
    GetAddrScale(const phxqueue::comm::proto::GetAddrScaleRequest &req,
                 phxqueue::comm::proto::GetAddrScaleResponse &resp);
    virtual phxqueue::comm::RetCode
    GetLockInfo(const phxqueue::comm::proto::GetLockInfoRequest &req,
                phxqueue::comm::proto::GetLockInfoResponse &resp);
    virtual phxqueue::comm::RetCode
    AcquireLock(const phxqueue::comm::proto::AcquireLockRequest &req,
                phxqueue::comm::proto::AcquireLockResponse &resp);

    virtual void BeforeLock(const phxqueue::comm::proto::ConsumerContext &cc);
    virtual void AfterLock(const phxqueue::comm::proto::ConsumerContext &cc);

};


}  // namespace test

}  // namespace skphxqueue

