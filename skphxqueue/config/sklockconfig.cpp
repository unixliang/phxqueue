#include "skphxqueue/config/proto/sklockconfig.pb.h"
#include "skphxqueue/config/sklockconfig.h"


namespace skphxqueue {

namespace config {


int SKLockConfig::Read(Comm::CConfig *conf, bool reload) {
    proto::LockConfig skproto;
    phxqueue::config::proto::LockConfig proto;

    if (NeedCheck()) {
        mmsection2pb::ConfigSectionLoaderWithCheck section_loader(conf);
        mmsection2pb::ParseSection(&section_loader, &skproto);
        assert(!section_loader.Error());
    } else {
        mmsection2pb::ConfigSectionLoader section_loader(conf);
        mmsection2pb::ParseSection(&section_loader, &skproto);
    }


    string buf;
    skproto.SerializeToString(&buf);
    proto.ParseFromString(buf);

    if (skproto.locks_size() != proto.locks_size()) {
        MMERR("ERR: skproto.locks_size()(%d) != proto.locks_size()(%d)",
              skproto.locks_size(), proto.locks_size());
        return -1;
    }

    for (int i{0}; i < skproto.locks_size(); ++i) {
        auto &&sklock = skproto.locks(i);
        auto &&lock = proto.mutable_locks(i);
        for (int j{0}; j < sklock.addrs_size(); ++j) {
            auto &&addrbuf = sklock.addrs(j);
            vector<string> arr;
            Comm::StrSplitList(addrbuf.c_str(), ":", false, arr);
            if (arr.size() != 3) continue;

            auto &&addr = lock->add_addrs();
            addr->set_ip(arr[0]);
            addr->set_port(stoi(arr[1]));
            addr->set_paxos_port(stoi(arr[2]));
        }
    }

    phxqueue::config::LockConfig::FillConfig(move(proto));

    return 0;
}


}  // namespace config

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

