#pragma once

#include <memory>

#include "phxqueue/producer.h"


namespace skphxqueue {

namespace producer {


class SKProducer : public phxqueue::producer::Producer {
  public:
    SKProducer(const phxqueue::producer::ProducerOption &opt)
            : phxqueue::producer::Producer(opt) {}
    virtual ~SKProducer() {}

    virtual void SetUserCookies(phxqueue::comm::proto::Cookies &user_cookie);
    virtual void CompressBuffer(const std::string &buffer,
                                std::string &compress_buffer, int &buffer_type);
    virtual std::unique_ptr<phxqueue::producer::StoreSelector>
    NewStoreSelector(const int topic_id, const int pub_id,
                     const uint64_t uin, const bool retry_switch_store = false);
};


}  // namespace producer

}  // namespace skphxqueue

