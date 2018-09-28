#include "skphxqueue/comm/utils/callgraph_util.h"

#include <cstring>
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <string>

#include "iOssAttr.h"
#include "iSvrkit.h"
#include "iLog.h"

//#include "co_routine.h"


namespace skphxqueue {

namespace comm {

namespace utils {

using namespace Comm;

void PrintCallGraphInfo() {
	Comm::DyeLogInfo_t dl;
	Comm::GetDyeLogInfo(&dl);

    Comm::MMSystemReqCookie *sc = Comm::GetSysReqCookie();

    std::ostringstream dl_callstack_oss, sc_callstack_oss;
    std::string dl_callstack, sc_callstack;

    // dl_callstack_oss
    {
        dl_callstack_oss << "[";
        for (unsigned int i{0}; i < dl.call_stack.size && i < 3; ++i) {
            dl_callstack_oss << " " << dl.call_stack.ossid_cmdid[2 * i] << " " << dl.call_stack.ossid_cmdid[2 * i + 1];
        }
        dl_callstack_oss << " ]";
        dl_callstack = dl_callstack_oss.str();
    }
    // sc_callstack_oss
    {
        sc_callstack_oss << "[";
        for (int i{0}; i < sc->call_stack_size(); ++i) {
            sc_callstack_oss << " " << sc->call_stack(i).ossid() << " " << sc->call_stack(i).cmdid();
        }
        sc_callstack_oss << " ]";
        sc_callstack = sc_callstack_oss.str();
    }

    MMINTERNAL("sc.uin %u sc.cmdid %d sc.servicetype %d sc.graphID %u sc.graphNodeID %u "
               "sc.call_stack.size %d sc.call_stack %s "
               "dl.graphID %u dl.graphNodeID %u "
               "dl.call_stack.size %d dl.call_stack %s",
               sc->uin(), sc->cmdid(), sc->servicetype(), sc->graph_id(), sc->graph_node_id(),
               sc->call_stack_size(), sc_callstack.c_str(),
               dl.graphID, dl.graphNodeID,
               dl.call_stack.size, dl_callstack.c_str());
}


}  // namespace utils

}  // namespace comm

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

