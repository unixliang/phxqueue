#include "skphxqueue/comm/skossconfig.h"

#include "iLog.h"

#include "mmsection2pb.h"


namespace skphxqueue {

namespace comm {


class SKOssConfig::SKOssConfigImpl {
  public:
    SKOssConfigImpl() {}
    virtual ~SKOssConfigImpl() {}

    vector<shared_ptr<proto::OssInfo>> oss_infos;
};

SKOssConfig::SKOssConfig() : impl_(new SKOssConfigImpl()) {}

SKOssConfig::~SKOssConfig() {}

int SKOssConfig::Read(Comm::CConfig *conf, bool reload) {
    proto::SKOssConfig proto;

    mmsection2pb::ConfigSectionLoader section_loader(conf);
    mmsection2pb::ParseSection(&section_loader, &proto);

    impl_->oss_infos.clear();

    for (int i{0}; i < proto.oss_infos_size(); ++i) {
        auto &&oss_info = proto.oss_infos(i);
        impl_->oss_infos.push_back(make_shared<proto::OssInfo>(oss_info));
    }

    return 0;
}

void SKOssConfig::GetOssInfos(vector<shared_ptr<proto::OssInfo>> &oss_infos) {
    oss_infos = impl_->oss_infos;
}


}  // namespace comm

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

