#include <cinttypes>
#include <array>

#include "iLog.h"

#include "phxqueue/comm.h"
#include "phxqueue/config.h"

#include "skphxqueue/plugin.h"

#include "skphxqueue/comm/skbreakpoint.h"
#include "skphxqueue/comm/skossconfig.h"


namespace skphxqueue {

namespace comm {


using namespace Comm;
using namespace std;


static void GetMatchedOssInfos(vector<shared_ptr<comm::proto::OssInfo>> &oss_infos,
                               const int topic_id = -1,
                               const int store_id = -1,
                               const int queue_id = -1,
                               const int consumer_group_id = -1,
                               const int pub_id = -1,
                               const int handle_id = -1,
                               const uint64_t uin = 0) {
    static __thread SKOssConfig oss_config;
    static __thread string oss_config_path;
    if (oss_config_path.empty()) {
        auto bpf = dynamic_cast<plugin::SKBreakPointFactory *>(phxqueue::plugin::BreakPointFactory::GetInstance());
        if (bpf) oss_config_path = bpf->GetOssFilePath();
        else oss_config_path = "not_exist.conf";
    }
    oss_config.SetFileIfUnset(oss_config_path.c_str());
    oss_config.LoadIfModified();

    vector<shared_ptr<comm::proto::OssInfo>> all_oss_infos;
    oss_config.GetOssInfos(all_oss_infos);
    for (auto &&oss_info : all_oss_infos) {
        if ((-1 == topic_id || -1 == oss_info->topic_id() || topic_id == oss_info->topic_id()) &&
            (-1 == store_id || -1 == oss_info->store_id() || store_id == oss_info->store_id()) &&
            (-1 == queue_id || -1 == oss_info->queue_id() || queue_id == oss_info->queue_id()) &&
            (-1 == consumer_group_id || -1 == oss_info->consumer_group_id() || consumer_group_id == oss_info->consumer_group_id()) &&
            (-1 == pub_id || -1 == oss_info->pub_id() || pub_id == oss_info->pub_id()) &&
            (-1 == handle_id || -1 == oss_info->handle_id() || handle_id == oss_info->handle_id()) &&
            (0 == uin || 0 == oss_info->uin() || uin == oss_info->uin())) {

            oss_infos.push_back(move(oss_info));
        }
    }
}

static inline void MyOssAttrInc(const int id, const int key, const int val) {
    if (id) OssAttrInc(id, key, val);
}

static inline void MyOssAttrSet(const int id, const int key, const int val) {
    if (id) OssAttrSet(id, key, val);
}

/*
static void OssAttrUsedTimeMS(const int ossid, const int osskey_base, const int used_time_ms) {
    if (ossid) {
        int osskey_step = 0;
        if (used_time_ms < 1) {
            osskey_step = 0;
        } else if (used_time_ms < 2) {
            osskey_step = 1;
        } else if (used_time_ms < 5) {
            osskey_step = 2;
        } else if (used_time_ms < 10) {
            osskey_step = 3;
        } else if (used_time_ms < 20) {
            osskey_step = 4;
        } else if (used_time_ms < 50) {
            osskey_step = 5;
        } else if (used_time_ms < 100) {
            osskey_step = 6;
        } else if (used_time_ms < 200) {
            osskey_step = 7;
        } else if (used_time_ms < 500) {
            osskey_step = 8;
        } else if (used_time_ms < 1000) {
            osskey_step = 9;
        } else if (used_time_ms < 2000) {
            osskey_step = 10;
        } else if (used_time_ms < 5000) {
            osskey_step = 11;
        } else if (used_time_ms < 10000) {
            osskey_step = 12;
        } else if (used_time_ms < 20000) {
            osskey_step = 13;
        } else {
            osskey_step = 14;
        }
        MyOssAttrInc(ossid, osskey_base + osskey_step, 1);
    }
}
*/

template<size_t SIZE>
void OssAttrIncForInterval(const int ossid, const int osskey_base, const int val, const array<int, SIZE> &arr) {
    int osskey_step = 0;
    for(auto &v : arr) {
        if (val >= v) ++osskey_step;
        else break;
    }
    MyOssAttrInc(ossid, osskey_base + osskey_step, 1);
}

// SKConsumerBP
void SKConsumerBP::OnChildRun(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 0, 1);
}
void SKConsumerBP::OnLock(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 1, 1);
}
void SKConsumerBP::OnLockSucc(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 2, 1);
}
void SKConsumerBP::OnProcess(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 3, 1);
}
void SKConsumerBP::OnProcessFail(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 4, 1);
}
void SKConsumerBP::OnProcessSucc(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 5, 1);
}
void SKConsumerBP::OnGetQueueDelayFail(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 6, 1);
}
void SKConsumerBP::OnLoop(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 7, 1);
}
void SKConsumerBP::OnLoopBreak(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 8, 1);
}
void SKConsumerBP::OnGet(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 9, 1);
}
void SKConsumerBP::OnGetFail(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 10, 1);
}
void SKConsumerBP::OnGetSucc(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 11, 1);
}
void SKConsumerBP::OnGetNoItem(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 12, 1);
}
void SKConsumerBP::OnSleepAfterGet(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 13, 1);
}
void SKConsumerBP::OnGetWithItem(const phxqueue::comm::proto::ConsumerContext &cc, const std::vector<std::shared_ptr<phxqueue::comm::proto::QItem>> &items) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 14, 1);
}
void SKConsumerBP::OnDropAll(const phxqueue::comm::proto::ConsumerContext &cc, const std::vector<std::shared_ptr<phxqueue::comm::proto::QItem>> &items) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 15, 1);
}
void SKConsumerBP::OnGetSizeTooSmall(const phxqueue::comm::proto::ConsumerContext &cc, const std::vector<std::shared_ptr<phxqueue::comm::proto::QItem>> &items) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 16, 1);
}

void SKConsumerBP::OnMemCheck(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 17, 1);
}
void SKConsumerBP::OnMemCheckUnpass(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 18, 1);
}
void SKConsumerBP::OnMemCheckPass(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 19, 1);
}

void SKConsumerBP::OnMaxLoopCheck(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 20, 1);
}
void SKConsumerBP::OnMaxLoopCheckUnpass(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 21, 1);
}
void SKConsumerBP::OnMaxLoopCheckPass(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer(), 22, 1);
}

// SKConsumerConsumeBP
void SKConsumerConsumeBP::OnConsumeThreadRun(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 0, 1);
}
void SKConsumerConsumeBP::OnConsumeThreadRunEnd(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 1, 1);
}
void SKConsumerConsumeBP::OnTaskDispatch(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 2, 1);
}
void SKConsumerConsumeBP::OnTaskWait(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 3, 1);
}
void SKConsumerConsumeBP::OnTaskDispatchFinish(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 4, 1);
}
void SKConsumerConsumeBP::OnMakeHandleBucket(const phxqueue::comm::proto::ConsumerContext &cc) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 5, 1);
}
void SKConsumerConsumeBP::OnHandleRoutineFunc(const phxqueue::comm::proto::ConsumerContext &cc, const int cid){
    Comm::SetLogWorkerIdx(cid + 1); // from 1

    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 6, 1);
}
void SKConsumerConsumeBP::OnHandle(const phxqueue::comm::proto::ConsumerContext &cc, const phxqueue::comm::proto::QItem &item) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id(), item.pub_id(), item.meta().handle_id(), item.meta().uin());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 7, 1);
}
void SKConsumerConsumeBP::OnHandleEnd(const phxqueue::comm::proto::ConsumerContext &cc, const phxqueue::comm::proto::QItem &item, const phxqueue::comm::HandleResult &handle_result) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id(), item.pub_id(), item.meta().handle_id(), item.meta().uin());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 8, 1);
        if (phxqueue::comm::HandleResult::RES_OK == handle_result) {
            MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 9, 1);
        } else if (phxqueue::comm::HandleResult::RES_ERROR == handle_result) {
            MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 10, 1);
        } else if (phxqueue::comm::HandleResult::RES_IGNORE == handle_result) {
            MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 11, 1);
        }
    }
}
void SKConsumerConsumeBP::OnBatchHandleRoutineFunc(const phxqueue::comm::proto::ConsumerContext &cc, const int cid) {
    Comm::SetLogWorkerIdx(10000);

    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 12, 1);
}
void SKConsumerConsumeBP::OnSkipHandle(const phxqueue::comm::proto::ConsumerContext &cc, const phxqueue::comm::proto::QItem &item) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, cc.topic_id(), cc.store_id(), cc.queue_id(), cc.consumer_group_id(), item.pub_id(), item.meta().handle_id(), item.meta().uin());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_consume(), 13, 1);
}


// SKConsumerHeartBeatLockBP
void SKConsumerHeartBeatLockBP::OnSync(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_hblock(), 0, 1);
}
void SKConsumerHeartBeatLockBP::OnProcUsed(const int topic_id, const int nproc, const int proc_used) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        OssAttrSetMax(oss_info->oss_attr_id_consumer_hblock(), 1, nproc);
        OssAttrSetMax(oss_info->oss_attr_id_consumer_hblock(), 2, proc_used);
    }
}
void SKConsumerHeartBeatLockBP::OnScaleHash(const int topic_id, const int consumer_group_id, const uint32_t scale_hash) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) OssAttrSetMax(oss_info->oss_attr_id_consumer_hblock_scale_hash(), consumer_group_id, scale_hash % 100000);
}
void SKConsumerHeartBeatLockBP::OnAdjustScale(const int topic_id, const int consumer_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_hblock(), 3, 1);
}
void SKConsumerHeartBeatLockBP::OnProcUsedExceed(const int topic_id, const int nproc, const int proc_used) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_hblock(), 4, 1);
}
void SKConsumerHeartBeatLockBP::OnSyncSucc(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_hblock(), 5, 1);
}
void SKConsumerHeartBeatLockBP::OnSyncFail(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_hblock(), 13, 1);
}

void SKConsumerHeartBeatLockBP::OnLock(const int topic_id, const int consumer_group_id, const int store_id, const int queue_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_hblock(), 6, 1);
}
void SKConsumerHeartBeatLockBP::OnProcLack(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_hblock(), 7, 1);
}
void SKConsumerHeartBeatLockBP::OnNoLockTarget(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_hblock(), 8, 1);
}
void SKConsumerHeartBeatLockBP::OnSkipLock(const int topic_id, const int consumer_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_hblock(), 9, 1);
}
void SKConsumerHeartBeatLockBP::OnLockSucc(const int topic_id, const int consumer_group_id, const int store_id, const int queue_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_hblock(), 11, 1);
}
void SKConsumerHeartBeatLockBP::OnLockFail(const int topic_id, const int consumer_group_id, const int store_id, const int queue_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_consumer_hblock(), 12, 1);
}

// SKStoreBP
void SKStoreBP::OnAdd(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 0, 1);
}
void SKStoreBP::OnAddRequestInvalid(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 1, 1);
}
void SKStoreBP::OnAddCheckMasterUnpass(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 2, 1);
}
void SKStoreBP::OnAddCheckMasterPass(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 3, 1);
}
void SKStoreBP::OnAddSkip(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 13, 1);
}
void SKStoreBP::OnPaxosAdd(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 4, 1);
}
void SKStoreBP::OnBatchPropose(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 5, 1);
}
void SKStoreBP::OnBatchProposeErr(const phxqueue::comm::proto::AddRequest &req, const uint64_t used_time_ms) {
    array<int, 14> intervals = {1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000};

    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_store(), 6, 1);
        //OssAttrUsedTimeMS(oss_info->oss_attr_id_store(), 51, used_time_ms);// key 51 - 65
        OssAttrIncForInterval(oss_info->oss_attr_id_store(), 51, used_time_ms, intervals);// key 51 - 65
    }
}
void SKStoreBP::OnBatchProposeErrTimeout(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 7, 1);
}
void SKStoreBP::OnBatchProposeErrTooManyThreadWaitingReject(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 8, 1);
}
void SKStoreBP::OnBatchProposeErrValueSizeTooLarge(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 9, 1);
}
void SKStoreBP::OnBatchProposeErrOther(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 10, 1);
}
void SKStoreBP::OnBatchProposeSucc(const phxqueue::comm::proto::AddRequest &req, const uint64_t instance_id, const uint32_t batch_idx, const uint64_t used_time_ms) {
    array<int, 14> intervals = {1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000 };

    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_store(), 11, 1);
        MyOssAttrInc(oss_info->oss_attr_id_store(), 12, req.items_size());
        //OssAttrUsedTimeMS(oss_info->oss_attr_id_store(), 66, used_time_ms);// key 66 - 80
        OssAttrIncForInterval(oss_info->oss_attr_id_store(), 66, used_time_ms, intervals);// key 66 - 80
    }
}

void SKStoreBP::OnGet(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 20, 1);
}
void SKStoreBP::OnGetRequestInvalid(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 21, 1);
    MMERR("ERR: OnGetRequestInvalid.");
}
void SKStoreBP::OnGetCheckMasterUnpass(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 22, 1);
}
void SKStoreBP::OnGetCheckMasterPass(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 23, 1);
}
void SKStoreBP::OnBaseMgrGet(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 24, 1);
}
void SKStoreBP::OnBaseMgrGetFail(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 25, 1);
}
void SKStoreBP::OnBaseMgrGetSucc(const phxqueue::comm::proto::GetRequest &req, const phxqueue::comm::proto::GetResponse &resp) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_store(), 26, 1);
        MyOssAttrInc(oss_info->oss_attr_id_store(), 27, resp.items_size());
    }
}

void SKStoreBP::OnInit(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 40, 1);
}
void SKStoreBP::OnInitErrTopic(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 41, 1);
}
void SKStoreBP::OnInitErrBaseMgr(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 42, 1);
}
void SKStoreBP::OnInitErrSyncCtrl(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 43, 1);
}
void SKStoreBP::OnInitErrCPMgr(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 44, 1);
}
void SKStoreBP::OnInitErrPaxos(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 45, 1);
}
void SKStoreBP::OnInitSucc(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store(), 46, 1);
}

// SKStoreBaseMgrBP

void SKStoreBaseMgrBP::OnAdd(const phxqueue::comm::proto::AddRequest &req, const int queue_info_id) {
    array<int, 18> intervals_byte_size = {10, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000, 2000000, 5000000, 10000000};

    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 0, 1);

        MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 22, req.items_size());
        for (int i{0}; i < req.items_size(); ++i) {
            size_t byte_size = req.items(i).ByteSize();
            MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 23, byte_size);
            OssAttrIncForInterval(oss_info->oss_attr_id_store_basemgr(), 24, byte_size, intervals_byte_size);// key 24 - 42
			MMERR("pub %d queue %d clientid %s count %d handleid %d bytesize %zu",
					req.items(i).pub_id(), req.queue_id(), req.items(i).meta().client_id().c_str(), req.items(i).count(), req.items(i).handle_id(), byte_size);
        }

        MyOssAttrInc(oss_info->oss_attr_id_store_onadd_paxos_group_id(), req.queue_id() % 100, 1);
        MyOssAttrInc(oss_info->oss_attr_id_store_onadd_queue_info_id(), queue_info_id, 1);

    }
}
void SKStoreBaseMgrBP::OnAddSkip(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 1, 1);
}
void SKStoreBaseMgrBP::OnAddSucc(const phxqueue::comm::proto::AddRequest &req, const uint64_t instance_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 2, 1);
}
void SKStoreBaseMgrBP::OnGet(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 3, 1);
}
void SKStoreBaseMgrBP::OnAdjustNextCursorIDFail(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 4, 1);
}
void SKStoreBaseMgrBP::OnCursorIDNotFound(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 5, 1);
}
void SKStoreBaseMgrBP::OnCursorIDChange(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 6, 1);
}
void SKStoreBaseMgrBP::OnGetNoMoreItem(const phxqueue::comm::proto::GetRequest &req, const uint64_t cur_cursor_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 7, 1);
}
void SKStoreBaseMgrBP::OnGetItemsByCursorIDFail(const phxqueue::comm::proto::GetRequest &req, const uint64_t cursor_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 8, 1);

    MMERR("ERR: OnGetItemsByCursorIDFail topic_id %d store_id %d queue_id %d consumer_group_id %d cursor_id %" PRIu64,
          req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id(), cursor_id);
}
void SKStoreBaseMgrBP::OnGetLastItemNotChosenInPaxos(const phxqueue::comm::proto::GetRequest &req, const uint64_t cursor_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 9, 1);

    MMERR("WARN: OnGetItemsByCursorIDFail topic_id %d store_id %d queue_id %d consumer_group_id %d cursor_id %" PRIu64,
          req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id(), cursor_id);
}
void SKStoreBaseMgrBP::OnGetNoMoreItemBeforeATime(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 10, 1);
}
void SKStoreBaseMgrBP::OnGetSkip(const phxqueue::comm::proto::GetRequest &req, const phxqueue::comm::proto::QItem &item) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id(), item.pub_id(), item.meta().handle_id(), item.meta().uin());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 11, 1);

    MMINFO("INFO: OnGetSkip topic_id %d store_id %d queue_id %d consumer_group_id %d uin %" PRIu64 " handle_id %d hash %" PRIu64,
           req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id(),
           (uint64_t)item.meta().uin(), item.meta().handle_id(), (uint64_t)item.meta().hash());
}
void SKStoreBaseMgrBP::OnGetRespSizeExceed(const phxqueue::comm::proto::GetRequest &req, const size_t byte_size) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 12, 1);

    MMERR("ERR: OnGetRespSizeExceed topic_id %d store_id %d queue_id %d consumer_group_id %d byte_size %zu",
          req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id(), byte_size);
}
void SKStoreBaseMgrBP::OnGetItemTooBig(const phxqueue::comm::proto::GetRequest &req, const phxqueue::comm::proto::QItem &item) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id(), item.pub_id(), item.meta().handle_id(), item.meta().uin());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 13, 1);

    MMERR("ERR: OnGetItemTooBig topic_id %d store_id %d queue_id %d consumer_group_id %d uin %" PRIu64 " handle_id %d hash %" PRIu64,
          req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id(),
          (uint64_t)item.meta().uin(), item.meta().handle_id(), (uint64_t)item.meta().hash());
}
void SKStoreBaseMgrBP::OnUpdateCursorIDFail(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 14, 1);

    MMERR("ERR: OnUpdateCursorIDFail topic_id %d store_id %d queue_id %d consumer_group_id %d",
          req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
}
void SKStoreBaseMgrBP::OnItemInResp(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 15, 1);
}
void SKStoreBaseMgrBP::OnGetSucc(const phxqueue::comm::proto::GetRequest &req, const phxqueue::comm::proto::GetResponse &resp) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 16, 1);
        MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 17, resp.items_size());
    }

    {
        int max_sz = 0;
        int max_handle_id = 0;
        uint64_t max_key = 0;
        map<uint64_t, int> uin2sz;
        for (int i{0}; i < resp.items_size(); ++i) {
            auto &&item = resp.items(i);
            auto key = item.meta().uin();
            auto sz = ++uin2sz[key];
            if (sz > max_sz) {
                max_key = key;
                max_sz = sz;
                max_handle_id = item.meta().handle_id();
            }
        }
        MMERR("DEBUG: topic_id %d store_id %d queue_id %d consumer_group_id %d nitem %d max_sz %d max_key %" PRIu64 " max_handle_id %d",
              req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id(), resp.items_size(), max_sz, max_key, max_handle_id);
    }
}
void SKStoreBaseMgrBP::OnCrcCheckPass(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 18, 1);
}
void SKStoreBaseMgrBP::OnCrcCheckUnpass(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 19, 1);
}
void SKStoreBaseMgrBP::OnGetItemFromStoreMetaQueue(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 20, 1);
}
void SKStoreBaseMgrBP::OnGetItemBeforeCheckPoint(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 21, 1);
}
void SKStoreBaseMgrBP::OnGetLoopReachMaxTime(const phxqueue::comm::proto::GetRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id(), req.consumer_group_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_store_basemgr(), 43, 1);
}

// SKStoreIMMasterBP

void SKStoreIMMasterBP::OnIMMaster(const int topic_id, const int paxos_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_store_immaster(), paxos_group_id, 1);
    }
}

// SKStoreSnatchMasterBP

void SKStoreSnatchMasterBP::OnSnatchMaster(const int topic_id, const int paxos_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_store_snatch_master(), paxos_group_id, 1);
    }
}


// SKStoreBacklogBP

void SKStoreBacklogBP::OnBackLogReport(const int topic_id, const int consumer_group_id, const int queue_id, const int backlog) {
    phxqueue::comm::RetCode ret;

    shared_ptr<const phxqueue::config::TopicConfig> topic_config;
    if (phxqueue::comm::RetCode::RET_OK != (ret = phxqueue::config::GlobalConfig::GetThreadInstance()->GetTopicConfigByTopicID(topic_id, topic_config))) {
        MMERR("ERR: GetTopicConfigByTopicID ret %d topic_id %d", as_integer(ret), topic_id);
        return;
    }

    shared_ptr<const phxqueue::config::proto::QueueInfo> queue_info;
    if (phxqueue::comm::RetCode::RET_OK != (ret = topic_config->GetQueueInfoByQueue(queue_id, queue_info))) {
        MMERR("ERR: GetQueueInfoByQueue ret %d queue_id %d", as_integer(ret), queue_id);
        return;
    }

    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id, -1, queue_id, consumer_group_id);
    for (auto &&oss_info : oss_infos) {
        OssAttrSetMax(oss_info->oss_attr_id_store_backlog(), consumer_group_id, backlog);
    }
}


// SKProducerBP
void SKProducerBP::OnEnqueue(const int topic_id, const int pub_id, const int handle_id, const uint64_t uin) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id, -1, -1, -1, pub_id, handle_id, uin);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 0, 1);
}
void SKProducerBP::OnSelectAndAddFail(const int topic_id, const int pub_id, const int handle_id, const uint64_t uin) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id, -1, -1, -1, pub_id, handle_id, uin);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 1, 1);
}
void SKProducerBP::OnEnqueueSucc(const int topic_id, const int pub_id, const int handle_id, const uint64_t uin) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id, -1, -1, -1, pub_id, handle_id, uin);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 2, 1);
}
void SKProducerBP::OnSelectAndAdd(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_producer(), 3, 1);
        MyOssAttrInc(oss_info->oss_attr_id_producer(), 4, req.items_size());
    }
}
void SKProducerBP::OnTopicIDInvalid(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 5, 1);
}
void SKProducerBP::OnUseDefaultQueueSelector(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 6, 1);
}
void SKProducerBP::OnUseCustomQueueSelector(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 7, 1);
}
void SKProducerBP::OnGetQueueIDFail(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 8, 1);
}
void SKProducerBP::OnUseDefaultStoreSelector(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 9, 1);
}
void SKProducerBP::OnUseCustomStoreSelector(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 10, 1);
}
void SKProducerBP::OnGetStoreIDFail(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 11, 1);
}
void SKProducerBP::OnRawAddFail(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 12, 1);
}
void SKProducerBP::OnSelectAndAddSucc(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_producer(), 13, 1);
        MyOssAttrInc(oss_info->oss_attr_id_producer_store_id(), req.store_id() % 100, 1);
    }
}

void SKProducerBP::OnRawAdd(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_producer(), 14, 1);
        MyOssAttrInc(oss_info->oss_attr_id_producer(), 15, req.items_size());
    }
}
void SKProducerBP::OnMasterClientCallFail(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 16, 1);
}
void SKProducerBP::OnRawAddSucc(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 17, 1);
}

void SKProducerBP::OnMakeAddRequests(const int topic_id, const std::vector<std::shared_ptr<phxqueue::comm::proto::QItem>> &items) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 18, 1);
}
void SKProducerBP::OnValidTopicID(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 19, 1);
}
void SKProducerBP::OnValidPubID(const int topic_id, const int pub_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id, -1, -1, -1, pub_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 20, 1);
}
void SKProducerBP::OnItemSizeTooLarge(const int topic_id, const int pub_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id, -1, -1, -1, pub_id);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 21, 1);
}
void SKProducerBP::OnMakeAddRequestsSucc(const int topic_id, const std::vector<std::shared_ptr<phxqueue::comm::proto::QItem>> &items) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id, -1, -1, -1);
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 22, 1);
}
void SKProducerBP::OnCountLimit(const int topic_id, const int pub_id, const phxqueue::comm::proto::QItem &item) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id, -1, -1, -1, pub_id, item.meta().handle_id(), item.meta().uin());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 23, 1);
}
void SKProducerBP::OnBatchRawAdd(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 24, 1);
}
void SKProducerBP::OnBatchRawAddSucc(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 25, 1);
}
void SKProducerBP::OnBatchRawAddFail(const phxqueue::comm::proto::AddRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) MyOssAttrInc(oss_info->oss_attr_id_producer(), 26, 1);
}
void SKProducerBP::OnBatchStat(const phxqueue::comm::proto::AddRequest &req, const phxqueue::comm::RetCode &retcode, const uint64_t time_wait_ms, bool is_timeout) {
    array<int, 14> intervals_time_wait = {1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000};
    array<int, 9> intervals_item_size = {1, 2, 5, 10, 20, 40, 60, 80, 100};

    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.store_id(), req.queue_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_producer(), 27, 1);
        MyOssAttrInc(oss_info->oss_attr_id_producer(), phxqueue::comm::RetCode::RET_OK == retcode ? 28 : 29, 1);
        if (is_timeout) MyOssAttrInc(oss_info->oss_attr_id_producer(), 30, 1);
        MyOssAttrInc(oss_info->oss_attr_id_producer(), 31, time_wait_ms);
        OssAttrIncForInterval(oss_info->oss_attr_id_store(), 32, time_wait_ms, intervals_time_wait);// key 32 - 46
        OssAttrIncForInterval(oss_info->oss_attr_id_store(), 47, req.items_size(), intervals_item_size);// key 47 - 56
    }
}

// ProducerConsumerGroupBP
void SKProducerConsumerGroupBP::OnConsumerGroupDistribute(const int topic_id, const int pub_id, const int handle_id, const uint64_t uin, const std::set<int> *consumer_group_ids) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id, -1, -1, -1, pub_id, handle_id, uin);
    for (auto &&oss_info : oss_infos) {
        if (!consumer_group_ids) {
            MyOssAttrInc(oss_info->oss_attr_id_producer_consumer_group(), 0, 1);
        } else {
            for (auto &&consumer_group_id : *consumer_group_ids) {
                MyOssAttrInc(oss_info->oss_attr_id_producer_consumer_group(), consumer_group_id, 1);
            }
        }
    }
}


// SKSchedulerBP

void SKSchedulerBP::OnInit() {
}
void SKSchedulerBP::OnDispose() {
}

void SKSchedulerBP::OnGetAddrScale(const phxqueue::comm::proto::GetAddrScaleRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 0, 1);
    }
}
void SKSchedulerBP::OnGetAddrScaleSucc(const phxqueue::comm::proto::GetAddrScaleRequest &req, const phxqueue::comm::proto::GetAddrScaleResponse &resp) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 1, 1);
    }
}
void SKSchedulerBP::OnGetAddrScaleFail(const phxqueue::comm::proto::GetAddrScaleRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 2, 1);
    }
}
void SKSchedulerBP::OnGetLockInfoSucc(const phxqueue::comm::proto::GetLockInfoRequest &req, const phxqueue::comm::proto::GetLockInfoResponse &resp) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.lock_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 3, 1);
    }
}
void SKSchedulerBP::OnGetLockInfoFail(const phxqueue::comm::proto::GetLockInfoRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.lock_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 4, 1);
    }
}
void SKSchedulerBP::OnAcquireLockSucc(const phxqueue::comm::proto::AcquireLockRequest &req, const phxqueue::comm::proto::AcquireLockResponse &resp) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.lock_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 5, 1);
    }
}
void SKSchedulerBP::OnAcquireLockFail(const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id(), req.lock_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 6, 1);
    }
}


// SKSchedulerMgrBP

void SKSchedulerMgrBP::OnInit() {
}
void SKSchedulerMgrBP::OnDispose() {
}
void SKSchedulerMgrBP::OnIMMaster(const phxqueue::comm::proto::GetAddrScaleRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 12, 1);
    }
}
void SKSchedulerMgrBP::OnIMNotMaster(const phxqueue::comm::proto::GetAddrScaleRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 13, 1);
    }
}
void SKSchedulerMgrBP::OnGetAddrScale(const phxqueue::comm::proto::GetAddrScaleRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 14, 1);
    }
}
void SKSchedulerMgrBP::OnConsumerNotFound(const phxqueue::comm::proto::GetAddrScaleRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 15, 1);
    }
}
void SKSchedulerMgrBP::OnUpdateStickyLoad(const phxqueue::comm::proto::GetAddrScaleRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 16, 1);
    }
}
void SKSchedulerMgrBP::OnBuildTopicScaleResponseSucc(const phxqueue::comm::proto::GetAddrScaleRequest &req, const phxqueue::comm::proto::GetAddrScaleResponse &resp) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 17, 1);
    }
}
void SKSchedulerMgrBP::OnBuildTopicScaleResponseFail(const phxqueue::comm::proto::GetAddrScaleRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler(), 18, 1);
    }
}

// SKSchedulerLoadBalanceBP

void SKSchedulerLoadBalanceBP::OnInit() {
}
void SKSchedulerLoadBalanceBP::OnDispose() {
}
void SKSchedulerLoadBalanceBP::OnLoadBalance(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 0, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnReloadConsumerConfigFail(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 1, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnReloadConsumerConfigSucc(const int topic_id, const bool consumer_conf_modified) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 2, 1);
        if (consumer_conf_modified) MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 3, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnConsumerAdd(const int topic_id, const phxqueue::comm::proto::Addr &addr) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 4, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnConsumerRemove(const int topic_id, const phxqueue::comm::proto::Addr &addr) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 5, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnConsumerChange(const int topic_id, const int nconsumer) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 6, 1);
        OssAttrSetMax(oss_info->oss_attr_id_scheduler_load_balance(), 7, nconsumer);
    }
}
void SKSchedulerLoadBalanceBP::OnDynamicMode(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 8, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnUpdateLiveFail(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 9, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnUpdateLiveSucc(const int topic_id, const bool live_modified) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 10, 1);
        if (live_modified) MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 11, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnConsumerNewDie(const int topic_id, const phxqueue::comm::proto::Addr &addr) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 12, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnConsumerNewLive(const int topic_id, const phxqueue::comm::proto::Addr &addr) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 13, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnGetMeanLoadFail(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 14, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnGetMeanLoadSucc(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 15, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnCheckImbalanceFail(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 16, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnCheckImbalanceSucc(const int topic_id, const double mean_load, const bool balanced) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 17, 1);
        OssAttrSetMax(oss_info->oss_attr_id_scheduler_load_balance(), 18, (int)mean_load);
        if (balanced) MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 19, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnAdjustScaleFail(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 20, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnAdjustScaleSucc(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 21, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnPreviewAdjustChange(const int topic_id, const phxqueue::comm::proto::Addr &addr, const int init_weight, const int old_weight, const int new_weight) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 22, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnPreviewAdjustUnchange(const int topic_id, const phxqueue::comm::proto::Addr &addr, const int init_weight, const int cur_weight) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 23, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnAdjustApply(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 24, 1);
    }
}
void SKSchedulerLoadBalanceBP::OnAdjustNotApply(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_load_balance(), 25, 1);
    }
}

// SKSchedulerKeepMasterBP
void SKSchedulerKeepMasterBP::OnInit() {
}
void SKSchedulerKeepMasterBP::OnDispose() {
}
void SKSchedulerKeepMasterBP::OnKeepMaster(const int topic_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_keep_master(), 0, 1);
    }
}
void SKSchedulerKeepMasterBP::OnRawGetLockInfoFail(const int topic_id, const phxqueue::comm::proto::GetLockInfoRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_keep_master(), 1, 1);
    }
}
void SKSchedulerKeepMasterBP::OnRawGetLockInfoSucc(const int topic_id, const phxqueue::comm::proto::GetLockInfoRequest &req, const phxqueue::comm::proto::GetLockInfoResponse &resp) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_keep_master(), 2, 1);
    }
}
void SKSchedulerKeepMasterBP::OnAcquireLock(const int topic_id, const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_keep_master(), 3, 1);
    }
}
void SKSchedulerKeepMasterBP::OnAcquireLockSucc(const int topic_id, const phxqueue::comm::proto::AcquireLockRequest &req, const phxqueue::comm::proto::AcquireLockResponse &resp) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_keep_master(), 4, 1);
    }
}
void SKSchedulerKeepMasterBP::OnAcquireLockFail(const int topic_id, const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_scheduler_keep_master(), 5, 1);
    }
}


// SKLockBP

void SKLockBP::OnInit(const int topic_id) {}
void SKLockBP::OnDispose(const int topic_id) {}

void SKLockBP::OnPaxosSetString(const phxqueue::comm::proto::SetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 6, 1);
    }
}
void SKLockBP::OnPaxosAcquireLock(const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 7, 1);
    }
}

void SKLockBP::OnSetStringPropose(const phxqueue::comm::proto::SetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 17, 1);
    }
}
void SKLockBP::OnSetStringProposeErr(const phxqueue::comm::proto::SetStringRequest &req,
                                     const uint64_t used_time_ms) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 18, 1);
    }
}
void SKLockBP::OnSetStringProposeErrTimeout(const phxqueue::comm::proto::SetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 19, 1);
    }
}
void SKLockBP::OnSetStringProposeErrTooManyThreadWaitingReject(const phxqueue::comm::proto::SetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 20, 1);
    }
}
void SKLockBP::OnSetStringProposeErrValueSizeTooLarge(const phxqueue::comm::proto::SetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 21, 1);
    }
}
void SKLockBP::OnSetStringProposeErrOther(const phxqueue::comm::proto::SetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 22, 1);
    }
}
void SKLockBP::OnSetStringProposeErrResult(const phxqueue::comm::proto::SetStringRequest &req,
                                           const uint64_t instance_id, const uint64_t used_time_ms) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 23, 1);
    }
}
void SKLockBP::OnSetStringProposeSucc(const phxqueue::comm::proto::SetStringRequest &req,
                                      const uint64_t instance_id, const uint64_t used_time_ms) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 24, 1);
    }
}

void SKLockBP::OnAcquireLockPropose(const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 25, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 8, 1);
    }
}
void SKLockBP::OnAcquireLockProposeErr(const phxqueue::comm::proto::AcquireLockRequest &req,
                                       const uint64_t used_time_ms) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 26, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 9, 1);
    }
}
void SKLockBP::OnAcquireLockProposeErrTimeout(const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 27, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 10, 1);
    }
}
void SKLockBP::OnAcquireLockProposeErrTooManyThreadWaitingReject(const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 28, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 11, 1);
    }
}
void SKLockBP::OnAcquireLockProposeErrValueSizeTooLarge(const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 29, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 12, 1);
    }
}
void SKLockBP::OnAcquireLockProposeErrOther(const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 30, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 13, 1);
    }
}
void SKLockBP::OnAcquireLockProposeErrResult(const phxqueue::comm::proto::AcquireLockRequest &req,
                                             const uint64_t instance_id, const uint64_t used_time_ms) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 31, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 14, 1);
    }
}
void SKLockBP::OnAcquireLockProposeSucc(const phxqueue::comm::proto::AcquireLockRequest &req,
                                        const uint64_t instance_id, const uint64_t used_time_ms) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 32, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 15, 1);
    }
}

void SKLockBP::OnGetString(const phxqueue::comm::proto::GetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 51, 1);
    }
}
void SKLockBP::OnGetStringRequestInvalid(const phxqueue::comm::proto::GetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 52, 1);
    }
}
void SKLockBP::OnGetStringCheckMasterPass(const phxqueue::comm::proto::GetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 53, 1);
    }
}

void SKLockBP::OnSetString(const phxqueue::comm::proto::SetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 54, 1);
    }
}
void SKLockBP::OnSetStringRequestInvalid(const phxqueue::comm::proto::SetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 55, 1);
    }
}
void SKLockBP::OnSetStringCheckMasterPass(const phxqueue::comm::proto::SetStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 56, 1);
    }
}

void SKLockBP::OnDeleteString(const phxqueue::comm::proto::DeleteStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 57, 1);
    }
}
void SKLockBP::OnDeleteStringRequestInvalid(const phxqueue::comm::proto::DeleteStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 58, 1);
    }
}
void SKLockBP::OnDeleteStringCheckMasterPass(const phxqueue::comm::proto::DeleteStringRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 59, 1);
    }
}

void SKLockBP::OnGetLockInfo(const phxqueue::comm::proto::GetLockInfoRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 60, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 4, 1);
    }
}
void SKLockBP::OnGetLockInfoRequestInvalid(const phxqueue::comm::proto::GetLockInfoRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 61, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 5, 1);
    }
}
void SKLockBP::OnGetLockInfoCheckMasterPass(const phxqueue::comm::proto::GetLockInfoRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 62, 1);
    }
}

void SKLockBP::OnAcquireLock(const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 63, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 1, 1);
    }
}
void SKLockBP::OnAcquireLockRequestInvalid(const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 64, 1);
        // TODO: deprecated
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 2, 1);
    }
}
void SKLockBP::OnAcquireLockCheckMasterPass(const phxqueue::comm::proto::AcquireLockRequest &req) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, req.topic_id());
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 65, 1);
    }
}


// SKLockMgrBP

void SKLockMgrBP::OnReadCheckpoint(const int topic_id, const uint32_t i) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 33, 1);
    }
}
void SKLockMgrBP::OnWriteCheckpoint(const int topic_id, const uint32_t i,
                                    uint64_t const checkpoint) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 34, 1);
    }
}

void SKLockMgrBP::OnReadRestartCheckpoint(const int topic_id, const uint32_t i) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 35, 1);
    }
}
void SKLockMgrBP::OnWriteRestartCheckpoint(const int topic_id, const uint32_t i,
                                           uint64_t const checkpoint) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 36, 1);
    }
}


// SKLockDbBP

void SKLockDbBP::OnVersionSetString(const bool sync) {
}

void SKLockDbBP::OnVersionDeleteString(const bool sync) {
}

void SKLockDbBP::OnAcquireLock(const bool sync) {
}


// SKLockCleanThreadBP

void SKLockCleanThreadBP::OnProposeCleanSucc(const int topic_id, const int paxos_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 111, 1);
    }
}
void SKLockCleanThreadBP::OnProposeCleanErr(const int topic_id, const int paxos_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 112, 1);
    }
}

void SKLockCleanThreadBP::OnNrKey(const int topic_id, const int nr) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrSet(oss_info->oss_attr_id_lock(), 116, nr);
    }
}
void SKLockCleanThreadBP::OnNrCleanKey(const int topic_id, const int nr) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrSet(oss_info->oss_attr_id_lock(), 117, nr);
    }
}


// SKLockKeepMasterThreadBP

void SKLockKeepMasterThreadBP::OnProposeMasterSucc(const int topic_id, const int paxos_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 121, 1);
    }
}
void SKLockKeepMasterThreadBP::OnProposeMasterErr(const int topic_id, const int paxos_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock(), 122, 1);
    }
}


// SKLockIMMasterBP

void SKLockIMMasterBP::OnIMMaster(const int topic_id, const int paxos_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock_immaster(), paxos_group_id, 1);
    }
}


// SKLockSnatchMasterBP

void SKLockSnatchMasterBP::OnSnatchMaster(const int topic_id, const int paxos_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock_snatch_master(), paxos_group_id, 1);
    }
}


// SKLockSMBP

void SKLockSMBP::OnExecute(const int topic_id, const int paxos_group_id,
                           const uint64_t instance_id, const string &paxos_value) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock_sm(), 1, 1);
    }
}
void SKLockSMBP::OnExecuteForCheckpoint(const int topic_id, const int paxos_group_id,
                                        const uint64_t instance_id,
                                        const string &paxos_value) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock_sm(), 2, 1);
    }
}
void SKLockSMBP::OnExecuteForCheckpointSync(const int topic_id, const int paxos_group_id,
                                            const uint64_t instance_id,
                                            const string &paxos_value) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock_sm(), 3, 1);
    }
}
void SKLockSMBP::OnExecuteForCheckpointNoSync(const int topic_id, const int paxos_group_id,
                                              const uint64_t instance_id,
                                              const string &paxos_value) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock_sm(), 4, 1);
    }
}
void SKLockSMBP::OnGetCheckpointInstanceID(const int topic_id, const int paxos_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock_sm(), 5, 1);
    }
}
void SKLockSMBP::OnGetCheckpointState(const int topic_id, const int paxos_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock_sm(), 6, 1);
    }
}
void SKLockSMBP::OnLoadCheckpointState(const int topic_id, const int paxos_group_id) {
    vector<shared_ptr<comm::proto::OssInfo>> oss_infos;
    GetMatchedOssInfos(oss_infos, topic_id);
    for (auto &&oss_info : oss_infos) {
        MyOssAttrInc(oss_info->oss_attr_id_lock_sm(), 7, 1);
    }
}


}  // namespace comm

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

