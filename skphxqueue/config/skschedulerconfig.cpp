#include "skphxqueue/config/skschedulerconfig.h"

#include <iostream>

#include "iLog.h"


namespace skphxqueue {

namespace config {


phxqueue::comm::RetCode SKSchedulerConfig::ReadConfig(typename phxqueue::config::SchedulerConfig::ProtoType &proto) {
    proto.Clear();
    MMDEBUG("start");

    Comm::CEndpointBucketVector *buckets = Comm::CBaseClientConfig::GetEndpointConfig()->GetList();
    if (!buckets) return phxqueue::comm::RetCode::RET_ERR_UNEXPECTED;

    auto &&scheduler = proto.mutable_scheduler();
    for (auto &&bucket : *buckets) {
        auto &&ep = bucket->GetEndpoint(0);
        if (!ep) continue;

        auto &&addr = scheduler->add_addrs();
        addr->set_ip(ep->GetIP());
        addr->set_port(ep->GetPort());
        addr->set_paxos_port(0);

        MMDEBUG("add addr ip %s port %d paxos_port %d",
                addr->ip().c_str(), addr->port(), addr->paxos_port());
    }

    return phxqueue::comm::RetCode::RET_OK;
}

}  // namespace config

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

