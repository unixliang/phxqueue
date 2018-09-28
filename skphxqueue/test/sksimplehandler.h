#include "skphxqueue/comm.h"


namespace skphxqueue {

namespace test {


class SKSimpleHandler : public phxqueue::comm::Handler {
  public:
    SKSimpleHandler() {}
    virtual ~SKSimpleHandler() {}

    virtual phxqueue::comm::HandleResult
    Handle(const phxqueue::comm::proto::ConsumerContext &cc,
           phxqueue::comm::proto::QItem &item, std::string &uncompressed_buffer);
};


}  // namespace test

}  // namespace skphxqueue

