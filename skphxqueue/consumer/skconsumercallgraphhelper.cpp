#include "skphxqueue/consumer/skconsumercallgraphhelper.h"

#include "iOssAttr.h"
#include "iSvrkit.h"
#include "iLog.h"


namespace skphxqueue {

namespace consumer {

using namespace Comm;
using namespace std;

SKConsumerCallGraphHelper::SKConsumerCallGraphHelper() {
}

SKConsumerCallGraphHelper::~SKConsumerCallGraphHelper() {
}

SKConsumerCallGraphHelper *SKConsumerCallGraphHelper::GetInstance() {
    static SKConsumerCallGraphHelper helper;
    return &helper;
}

void SKConsumerCallGraphHelper::Init(const int consumer_ossid) {
    consumer_ossid_ = consumer_ossid;
}


void SKConsumerCallGraphHelper::FixGraph() {
    // cookie是在cookie打包的，所以只能模拟writebroker调用consumer
    // 先模拟writebroker调用consumer
    // 再恢复consumer调用其它模块

    OssAttrInc(112480, 0, 1);

    Comm::DyeLogInfo_t dl; 
    Comm::GetDyeLogInfo(&dl);

    Comm::CallStack cs;
    Comm::GetLastCallStack(&cs);

    const uint32_t graph_id = dl.graphID;
    const int writebroker_ossid = cs.ossid();
    const int writebroker_cmdid = cs.cmdid();
    const uint32_t writebroker_graph_node_id = dl.graphNodeID; // writebroker的graph_node_id在dyeloginfo中
    const int consumer_ossid = consumer_ossid_;
    uint32_t consumer_graph_node_id;
    GenGraphNodeID(consumer_graph_node_id);

    OssAttrInc(112480, writebroker_ossid ? 1 : 2, 1);
    OssAttrInc(112480, writebroker_cmdid ? 3 : 4, 1);
    OssAttrInc(112480, writebroker_graph_node_id ? 5 : 6, 1); // graph_node_id为0的正常概率是1/65536
    OssAttrInc(112480, consumer_ossid ? 7 : 8, 1);
    OssAttrInc(112480, consumer_graph_node_id ? 9 : 10, 1); // graph_node_id为0的正常概率是1/65536
    OssAttrInc(112480, graph_id ? 18 : 19, 1); // 若graph_id为0，表示上层CGI未初始化callgraph，writebroker的graph_node_id也为0

    // writebroker->consumer
    {
        if (writebroker_ossid) {
            OssAttrInc(112480, 16, 1);

            SKChannelComm::SetCallGraphCurrentOssID(writebroker_ossid);
            SKChannelComm::SetCallGraphCurrentCmdID(writebroker_cmdid);
        } else {
            OssAttrInc(112480, 17, 1);
        }

        if (consumer_ossid) {
            OssAttrInc(112480, 12, 1);

            Comm::SKChannelComm::SetCallGraphNodeID(consumer_graph_node_id);
            Comm::CallGraphLog(LOGID_BASE::GetInnerIP(), consumer_ossid, 0, 0, 0, 0);
        } else {
            OssAttrInc(112480, 13, 1);
        }
    }

    // consumer->other
    if (consumer_ossid) {
        OssAttrInc(112480, 14, 1);

        Comm::SetGraphNodeID(consumer_graph_node_id);// 设置consumer的graph_node_id到dyeloginfo中
        SKChannelComm::SetCallGraphCurrentOssID(consumer_ossid);
        SKChannelComm::SetCallGraphCurrentCmdID(0);
    } else {
        OssAttrInc(112480, 15, 1);
    }

    // log
    Comm::LogDebug("%s dyeuin %u dyelevel %d dyecmd %u innerip %s writebroker_graph_node_id %d writebroker_ossid %d writebroker_cmdid %d consumer_graph_node_id %u consumer_ossid %d",
                   __func__, dl.uin, dl.logLevel, dl.cmdID, LOGID_BASE::GetInnerIP(),
                   writebroker_graph_node_id, writebroker_ossid, writebroker_cmdid,
                   consumer_graph_node_id, consumer_ossid);
}

}
}

//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

