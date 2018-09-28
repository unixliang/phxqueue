#include "skphxqueue/config/skstoreconfig.h"

#include "iLog.h"

#include "skphxqueue/config/proto/skstoreconfig.pb.h"


namespace skphxqueue {

namespace config {


int SKStoreConfig::Read(Comm::CConfig *conf, bool reload) {
    MMDEBUG("start");

    proto::StoreConfig skproto;
    phxqueue::config::proto::StoreConfig proto;

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

    if (skproto.stores_size() != proto.stores_size()) {
        MMERR("ERR: skproto.stores_size()(%d) != proto.stores_size()(%d)", skproto.stores_size(), proto.stores_size());
        return -1;
    }

    for (int i{0}; i < skproto.stores_size(); ++i) {
        auto &&skstore = skproto.stores(i);
        auto &&store = proto.mutable_stores(i);
        for (int j{0}; j < skstore.addrs_size(); ++j) {
            auto &&addrbuf = skstore.addrs(j);
            vector<string> arr;
            Comm::StrSplitList(addrbuf.c_str(), ":", false, arr);
            if (arr.size() != 3) continue;

            auto &&addr = store->add_addrs();
            addr->set_ip(arr[0]);
            addr->set_port(stoi(arr[1]));
            addr->set_paxos_port(stoi(arr[2]));

            MMDEBUG("add store ip %s port %d paxos_port %d", addr->ip().c_str(), addr->port(), addr->paxos_port());
        }
    }

    phxqueue::config::StoreConfig::FillConfig(move(proto));

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

