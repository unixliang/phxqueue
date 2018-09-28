#include "skphxqueue/comm/proto/skossconfig.pb.h"

#include "iFileFunc.h"


namespace skphxqueue {

namespace comm {


class SKOssConfig : public Comm::CBaseConfig {
  public:
    SKOssConfig();
    virtual ~SKOssConfig();

    virtual int Read(Comm::CConfig *conf, bool /* reload */);

    void GetOssInfos(std::vector<shared_ptr<proto::OssInfo>> &oss_infos);

  private:
    class SKOssConfigImpl;
    std::unique_ptr<SKOssConfigImpl> impl_;
};


}  // namespace comm

}  // namespace skphxqueue

