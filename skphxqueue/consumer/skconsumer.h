#pragma once

#include <memory>

#include "phxqueue/consumer.h"


namespace skphxqueue {

namespace consumer {


class SKConsumer : public phxqueue::consumer::Consumer {
  public:
    SKConsumer(const phxqueue::consumer::ConsumerOption &opt)
            : phxqueue::consumer::Consumer(opt) {}
    virtual ~SKConsumer() = default;

    virtual void BeforeFork();
    virtual void OnChildRun(const int vpid);
    virtual void OnRunSync();
    virtual void OnConsumeThreadRun(const int vpid);
    virtual void BeforeLock(const phxqueue::comm::proto::ConsumerContext &cc);
    virtual void BeforeGet(const phxqueue::comm::proto::GetRequest &req);

    virtual phxqueue::comm::RetCode
    UncompressBuffer(const std::string &buffer, const int buffer_type,
                     std::string &uncompressed_buffer);
    virtual void CompressBuffer(const std::string &buffer, std::string &compress_buffer,
                                const int buffer_type);
    virtual phxqueue::comm::RetCode
    GetQueueByAddrScale(const std::vector<phxqueue::consumer::Queue_t> &queues,
                        const phxqueue::consumer::AddrScales &addr_scales,
                        std::set<size_t> &queue_idxs);

  private:
    void RestoreUserCookies(const phxqueue::comm::proto::Cookies &user_cookies);
};


}  // namespace consumer

}  // namespace skphxqueue

