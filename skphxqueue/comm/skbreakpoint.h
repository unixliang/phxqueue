#pragma once

#include <memory>

#include "phxqueue/comm.h"


namespace skphxqueue {

namespace comm {


class SKConsumerBP : public phxqueue::comm::ConsumerBP {
  public:
    SKConsumerBP() : phxqueue::comm::ConsumerBP() {}
    virtual ~SKConsumerBP() override {}

    virtual void OnChildRun(const int topic_id) override;
    virtual void OnLock(const int topic_id) override;
    virtual void OnLockSucc(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnProcess(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnProcessFail(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnProcessSucc(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnGetQueueDelayFail(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnLoop(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnLoopBreak(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnGet(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnGetFail(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnGetSucc(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnGetNoItem(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnSleepAfterGet(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnGetWithItem(const phxqueue::comm::proto::ConsumerContext &cc, const std::vector<std::shared_ptr<phxqueue::comm::proto::QItem>> &items) override;
    virtual void OnDropAll(const phxqueue::comm::proto::ConsumerContext &cc, const std::vector<std::shared_ptr<phxqueue::comm::proto::QItem>> &items) override;
    virtual void OnGetSizeTooSmall(const phxqueue::comm::proto::ConsumerContext &cc, const std::vector<std::shared_ptr<phxqueue::comm::proto::QItem>> &items) override;
    virtual void OnFreeMemoryAfterLockFail(const int topic_id) override;

    virtual void OnMemCheck(const int topic_id) override;
    virtual void OnMemCheckUnpass(const int topic_id) override;
    virtual void OnMemCheckPass(const int topic_id) override;

    virtual void OnMaxLoopCheck(const int topic_id) override;
    virtual void OnMaxLoopCheckUnpass(const int topic_id) override;
    virtual void OnMaxLoopCheckPass(const int topic_id) override;
};


class SKConsumerConsumeBP : public phxqueue::comm::ConsumerConsumeBP{
  public:
    SKConsumerConsumeBP() : phxqueue::comm::ConsumerConsumeBP() {}
    virtual ~SKConsumerConsumeBP() override {}

    virtual void OnConsumeThreadRun(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnConsumeThreadRunEnd(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnTaskDispatch(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnTaskWait(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnTaskDispatchFinish(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnMakeHandleBucket(const phxqueue::comm::proto::ConsumerContext &cc) override;
    virtual void OnHandleRoutineFunc(const phxqueue::comm::proto::ConsumerContext &cc, const int cid) override;
    virtual void OnHandle(const phxqueue::comm::proto::ConsumerContext &cc, const phxqueue::comm::proto::QItem &item) override;
    virtual void OnHandleEnd(const phxqueue::comm::proto::ConsumerContext &cc, const phxqueue::comm::proto::QItem &item, const phxqueue::comm::HandleResult &handle_result) override;
    virtual void OnBatchHandleRoutineFunc(const phxqueue::comm::proto::ConsumerContext &cc, const int cid) override;
    virtual void OnSkipHandle(const phxqueue::comm::proto::ConsumerContext &cc, const phxqueue::comm::proto::QItem &item) override;
};


class SKConsumerHeartBeatLockBP : public phxqueue::comm::ConsumerHeartBeatLockBP {
  public:
    SKConsumerHeartBeatLockBP() : phxqueue::comm::ConsumerHeartBeatLockBP() {}
    virtual ~SKConsumerHeartBeatLockBP() override {}

    virtual void OnSync(const int topic_id) override;
    virtual void OnProcUsed(const int topic_id, const int nproc, const int proc_used) override;
    virtual void OnScaleHash(const int topic_id, const int consumer_group_id, const uint32_t scale_hash) override;
    virtual void OnAdjustScale(const int topic_id, const int consumer_group_id) override;
    virtual void OnProcUsedExceed(const int topic_id, const int nproc, const int proc_used) override;
    virtual void OnSyncSucc(const int topic_id) override;
    virtual void OnSyncFail(const int topic_id) override;

    virtual void OnLock(const int topic_id, const int consumer_group_id, const int store_id, const int queue_id) override;
    virtual void OnProcLack(const int topic_id) override;
    virtual void OnNoLockTarget(const int topic_id) override;
    virtual void OnSkipLock(const int topic_id, const int consumer_group_id) override;
    virtual void OnLockSucc(const int topic_id, const int consumer_group_id, const int store_id, const int queue_id) override;
    virtual void OnLockFail(const int topic_id, const int consumer_group_id, const int store_id, const int queue_id) override;
};


class SKStoreBP : public phxqueue::comm::StoreBP {
  public:
    SKStoreBP() : phxqueue::comm::StoreBP() {}
    virtual ~SKStoreBP() override {}

    virtual void OnAdd(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnAddRequestInvalid(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnAddCheckMasterUnpass(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnAddCheckMasterPass(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnAddSkip(const phxqueue::comm::proto::AddRequest &req) override;

    virtual void OnPaxosAdd(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnBatchPropose(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnBatchProposeErr(const phxqueue::comm::proto::AddRequest &req, const uint64_t used_time_ms) override;
    virtual void OnBatchProposeErrTimeout(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnBatchProposeErrTooManyThreadWaitingReject(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnBatchProposeErrValueSizeTooLarge(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnBatchProposeErrOther(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnBatchProposeSucc(const phxqueue::comm::proto::AddRequest &req, const uint64_t instance_id, const uint32_t batch_idx, const uint64_t used_time_ms) override;

    virtual void OnGet(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnGetRequestInvalid(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnGetCheckMasterUnpass(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnGetCheckMasterPass(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnBaseMgrGet(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnBaseMgrGetFail(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnBaseMgrGetSucc(const phxqueue::comm::proto::GetRequest &req, const phxqueue::comm::proto::GetResponse &resp) override;

    virtual void OnInit(const int topic_id) override;
    virtual void OnInitErrTopic(const int topic_id) override;
    virtual void OnInitErrBaseMgr(const int topic_id) override;
    virtual void OnInitErrSyncCtrl(const int topic_id) override;
    virtual void OnInitErrCPMgr(const int topic_id) override;
    virtual void OnInitErrPaxos(const int topic_id) override;
    virtual void OnInitSucc(const int topic_id) override;
};


class SKStoreBaseMgrBP : public phxqueue::comm::StoreBaseMgrBP {
  public:
    SKStoreBaseMgrBP() : StoreBaseMgrBP() {}
    virtual ~SKStoreBaseMgrBP() override {}

    virtual void OnAdd(const phxqueue::comm::proto::AddRequest &req, const int queue_info_id) override;
    virtual void OnAddSkip(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnAddSucc(const phxqueue::comm::proto::AddRequest &req, const uint64_t instance_id) override;

    virtual void OnGet(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnAdjustNextCursorIDFail(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnCursorIDNotFound(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnCursorIDChange(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnGetNoMoreItem(const phxqueue::comm::proto::GetRequest &req, const uint64_t cur_cursor_id) override;
    virtual void OnGetItemsByCursorIDFail(const phxqueue::comm::proto::GetRequest &req, const uint64_t cursor_id) override;
    virtual void OnGetLastItemNotChosenInPaxos(const phxqueue::comm::proto::GetRequest &req, const uint64_t cursor_id) override;
    virtual void OnGetNoMoreItemBeforeATime(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnGetSkip(const phxqueue::comm::proto::GetRequest &req, const phxqueue::comm::proto::QItem &item) override;
    virtual void OnGetRespSizeExceed(const phxqueue::comm::proto::GetRequest &req, const size_t byte_size) override;
    virtual void OnGetItemTooBig(const phxqueue::comm::proto::GetRequest &req, const phxqueue::comm::proto::QItem &item) override;
    virtual void OnUpdateCursorIDFail(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnItemInResp(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnGetSucc(const phxqueue::comm::proto::GetRequest &req, const phxqueue::comm::proto::GetResponse &resp) override;
    virtual void OnCrcCheckPass(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnCrcCheckUnpass(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnGetItemFromStoreMetaQueue(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnGetItemBeforeCheckPoint(const phxqueue::comm::proto::GetRequest &req) override;
    virtual void OnGetLoopReachMaxTime(const phxqueue::comm::proto::GetRequest &req) override;
};


class SKStoreIMMasterBP : public phxqueue::comm::StoreIMMasterBP {
  public:
    SKStoreIMMasterBP() : phxqueue::comm::StoreIMMasterBP() {}
    virtual ~SKStoreIMMasterBP() override {}

    virtual void OnIMMaster(const int topic_id, const int paxos_group_id) override;
};


class SKStoreSnatchMasterBP : public phxqueue::comm::StoreSnatchMasterBP {
  public:
    SKStoreSnatchMasterBP() : phxqueue::comm::StoreSnatchMasterBP() {}
    virtual ~SKStoreSnatchMasterBP() override {}

    virtual void OnSnatchMaster(const int topic_id, const int paxos_group_id) override;
};


class SKStoreBacklogBP : public phxqueue::comm::StoreBacklogBP{
  public:
    SKStoreBacklogBP() : phxqueue::comm::StoreBacklogBP() {}
    virtual ~SKStoreBacklogBP() override {}

    virtual void OnBackLogReport(const int topic_id, const int consumer_group_id, const int queue_id, const int backlog) override;
};


class SKProducerBP : public phxqueue::comm::ProducerBP {
  public:
    SKProducerBP() : phxqueue::comm::ProducerBP() {}
    virtual ~SKProducerBP() override {}

    virtual void OnEnqueue(const int topic_id, const int pub_id, const int handle_id, const uint64_t uin) override;
    virtual void OnSelectAndAddFail(const int topic_id, const int pub_id, const int handle_id, const uint64_t uin) override;
    virtual void OnEnqueueSucc(const int topic_id, const int pub_id, const int handle_id, const uint64_t uin) override;

    virtual void OnSelectAndAdd(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnTopicIDInvalid(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnUseDefaultQueueSelector(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnUseCustomQueueSelector(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnGetQueueIDFail(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnUseDefaultStoreSelector(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnUseCustomStoreSelector(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnGetStoreIDFail(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnRawAddFail(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnSelectAndAddSucc(const phxqueue::comm::proto::AddRequest &req) override;

    virtual void OnRawAdd(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnMasterClientCallFail(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnRawAddSucc(const phxqueue::comm::proto::AddRequest &req) override;

    virtual void OnMakeAddRequests(const int topic_id, const std::vector<std::shared_ptr<phxqueue::comm::proto::QItem>> &items) override;
    virtual void OnValidTopicID(const int topic_id) override;
    virtual void OnValidPubID(const int topic_id, const int pub_id) override;
    virtual void OnItemSizeTooLarge(const int topic_id, const int pub_id) override;
    virtual void OnMakeAddRequestsSucc(const int topic_id, const std::vector<std::shared_ptr<phxqueue::comm::proto::QItem>> &items) override;

    virtual void OnCountLimit(const int topic_id, const int pub_id, const phxqueue::comm::proto::QItem &item) override;

    virtual void OnBatchRawAdd(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnBatchRawAddSucc(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnBatchRawAddFail(const phxqueue::comm::proto::AddRequest &req) override;
    virtual void OnBatchStat(const phxqueue::comm::proto::AddRequest &req, const phxqueue::comm::RetCode &retcode, const uint64_t time_wait_ms, bool is_timeout) override;
};


class SKProducerConsumerGroupBP : public phxqueue::comm::ProducerConsumerGroupBP {
  public:
    SKProducerConsumerGroupBP() : phxqueue::comm::ProducerConsumerGroupBP() {}
    virtual ~SKProducerConsumerGroupBP() override {}

    virtual void OnConsumerGroupDistribute(const int topic_id, const int pub_id, const int handle_id, const uint64_t uin, const std::set<int> *consumer_group_ids) override;
};


class SKSchedulerBP : public phxqueue::comm::SchedulerBP {
  public:
    SKSchedulerBP() : phxqueue::comm::SchedulerBP() {}
    virtual ~SKSchedulerBP() override {}

    virtual void OnInit() override;
    virtual void OnDispose() override;

    virtual void OnGetAddrScale(const phxqueue::comm::proto::GetAddrScaleRequest &req) override;
    virtual void OnGetAddrScaleSucc(const phxqueue::comm::proto::GetAddrScaleRequest &req, const phxqueue::comm::proto::GetAddrScaleResponse &resp) override;
    virtual void OnGetAddrScaleFail(const phxqueue::comm::proto::GetAddrScaleRequest &req) override;

    virtual void OnGetLockInfoSucc(const phxqueue::comm::proto::GetLockInfoRequest &req, const phxqueue::comm::proto::GetLockInfoResponse &resp) override;
    virtual void OnGetLockInfoFail(const phxqueue::comm::proto::GetLockInfoRequest &req) override;

    virtual void OnAcquireLockSucc(const phxqueue::comm::proto::AcquireLockRequest &req, const phxqueue::comm::proto::AcquireLockResponse &resp) override;
    virtual void OnAcquireLockFail(const phxqueue::comm::proto::AcquireLockRequest &req) override;
};


class SKSchedulerMgrBP : public phxqueue::comm::SchedulerMgrBP {
  public:
    SKSchedulerMgrBP() : phxqueue::comm::SchedulerMgrBP() {}
    virtual ~SKSchedulerMgrBP() override {}

    virtual void OnInit() override;
    virtual void OnDispose() override;

    virtual void OnIMMaster(const phxqueue::comm::proto::GetAddrScaleRequest &req) override;
    virtual void OnIMNotMaster(const phxqueue::comm::proto::GetAddrScaleRequest &req) override;

    virtual void OnGetAddrScale(const phxqueue::comm::proto::GetAddrScaleRequest &req) override;
    virtual void OnConsumerNotFound(const phxqueue::comm::proto::GetAddrScaleRequest &req) override;
    virtual void OnUpdateStickyLoad(const phxqueue::comm::proto::GetAddrScaleRequest &req) override;
    virtual void OnBuildTopicScaleResponseSucc(const phxqueue::comm::proto::GetAddrScaleRequest &req, const phxqueue::comm::proto::GetAddrScaleResponse &resp) override;
    virtual void OnBuildTopicScaleResponseFail(const phxqueue::comm::proto::GetAddrScaleRequest &req) override;
};


class SKSchedulerLoadBalanceBP : public phxqueue::comm::SchedulerLoadBalanceBP {
  public:
    SKSchedulerLoadBalanceBP() : phxqueue::comm::SchedulerLoadBalanceBP() {}
    virtual ~SKSchedulerLoadBalanceBP() override {}

    virtual void OnInit() override;
    virtual void OnDispose() override;

    virtual void OnLoadBalance(const int topic_id) override;
    virtual void OnReloadConsumerConfigFail(const int topic_id) override;
    virtual void OnReloadConsumerConfigSucc(const int topic_id, const bool consumer_conf_modified) override;

    virtual void OnConsumerAdd(const int topic_id, const phxqueue::comm::proto::Addr &addr) override;
    virtual void OnConsumerRemove(const int topic_id, const phxqueue::comm::proto::Addr &addr) override;
    virtual void OnConsumerChange(const int topic_id, const int nconsumer) override;

    virtual void OnDynamicMode(const int topic_id) override;

    virtual void OnUpdateLiveFail(const int topic_id) override;
    virtual void OnUpdateLiveSucc(const int topic_id, const bool live_modified) override;

    virtual void OnConsumerNewDie(const int topic_id, const phxqueue::comm::proto::Addr &addr) override;
    virtual void OnConsumerNewLive(const int topic_id, const phxqueue::comm::proto::Addr &addr) override;

    virtual void OnGetMeanLoadFail(const int topic_id) override;
    virtual void OnGetMeanLoadSucc(const int topic_id) override;

    virtual void OnCheckImbalanceFail(const int topic_id) override;
    virtual void OnCheckImbalanceSucc(const int topic_id, const double mean_load, const bool balanced) override;

    virtual void OnAdjustScaleFail(const int topic_id) override;
    virtual void OnAdjustScaleSucc(const int topic_id) override;

    virtual void OnPreviewAdjustChange(const int topic_id, const phxqueue::comm::proto::Addr &addr, const int init_weight, const int old_weight, const int new_weight) override;
    virtual void OnPreviewAdjustUnchange(const int topic_id, const phxqueue::comm::proto::Addr &addr, const int init_weight, const int cur_weight) override;

    virtual void OnAdjustApply(const int topic_id) override;
    virtual void OnAdjustNotApply(const int topic_id) override;
};


class SKSchedulerKeepMasterBP : public phxqueue::comm::SchedulerKeepMasterBP {
  public:
    SKSchedulerKeepMasterBP() : phxqueue::comm::SchedulerKeepMasterBP() {}
    virtual ~SKSchedulerKeepMasterBP() override {}

    virtual void OnInit() override;
    virtual void OnDispose() override;

    virtual void OnKeepMaster(const int topic_id) override;
    virtual void OnRawGetLockInfoFail(const int topic_id, const phxqueue::comm::proto::GetLockInfoRequest &req) override;
    virtual void OnRawGetLockInfoSucc(const int topic_id, const phxqueue::comm::proto::GetLockInfoRequest &req, const phxqueue::comm::proto::GetLockInfoResponse &resp) override;

    virtual void OnAcquireLock(const int topic_id, const phxqueue::comm::proto::AcquireLockRequest &req) override;
    virtual void OnAcquireLockSucc(const int topic_id, const phxqueue::comm::proto::AcquireLockRequest &req, const phxqueue::comm::proto::AcquireLockResponse &resp) override;
    virtual void OnAcquireLockFail(const int topic_id, const phxqueue::comm::proto::AcquireLockRequest &req) override;
};


class SKLockBP : public phxqueue::comm::LockBP {
  public:
    SKLockBP() : phxqueue::comm::LockBP() {}
    virtual ~SKLockBP() override {}

    virtual void OnInit(const int topic_id) override;
    virtual void OnDispose(const int topic_id) override;

    virtual void OnPaxosSetString(const phxqueue::comm::proto::SetStringRequest &req) override;
    virtual void OnPaxosAcquireLock(const phxqueue::comm::proto::AcquireLockRequest &req) override;

    virtual void OnSetStringPropose(const phxqueue::comm::proto::SetStringRequest &req) override;
    virtual void OnSetStringProposeErr(const phxqueue::comm::proto::SetStringRequest &req,
                                       const uint64_t used_time_ms) override;
    virtual void OnSetStringProposeErrTimeout(const phxqueue::comm::proto::SetStringRequest &req) override;
    virtual void OnSetStringProposeErrTooManyThreadWaitingReject(const phxqueue::comm::proto::SetStringRequest &req) override;
    virtual void OnSetStringProposeErrValueSizeTooLarge(const phxqueue::comm::proto::SetStringRequest &req) override;
    virtual void OnSetStringProposeErrOther(const phxqueue::comm::proto::SetStringRequest &req) override;
    virtual void OnSetStringProposeErrResult(const phxqueue::comm::proto::SetStringRequest &req,
                                             const uint64_t instance_id, const uint64_t used_time_ms) override;
    virtual void OnSetStringProposeSucc(const phxqueue::comm::proto::SetStringRequest &req,
                                        const uint64_t instance_id, const uint64_t used_time_ms) override;

    virtual void OnAcquireLockPropose(const phxqueue::comm::proto::AcquireLockRequest &req) override;
    virtual void OnAcquireLockProposeErr(const phxqueue::comm::proto::AcquireLockRequest &req,
                                         const uint64_t used_time_ms) override;
    virtual void OnAcquireLockProposeErrTimeout(const phxqueue::comm::proto::AcquireLockRequest &req) override;
    virtual void OnAcquireLockProposeErrTooManyThreadWaitingReject(const phxqueue::comm::proto::AcquireLockRequest &req) override;
    virtual void OnAcquireLockProposeErrValueSizeTooLarge(const phxqueue::comm::proto::AcquireLockRequest &req) override;
    virtual void OnAcquireLockProposeErrOther(const phxqueue::comm::proto::AcquireLockRequest &req) override;
    virtual void OnAcquireLockProposeErrResult(const phxqueue::comm::proto::AcquireLockRequest &req,
                                               const uint64_t instance_id, const uint64_t used_time_ms) override;
    virtual void OnAcquireLockProposeSucc(const phxqueue::comm::proto::AcquireLockRequest &req,
                                          const uint64_t instance_id, const uint64_t used_time_ms) override;

    virtual void OnGetString(const phxqueue::comm::proto::GetStringRequest &req) override;
    virtual void OnGetStringRequestInvalid(const phxqueue::comm::proto::GetStringRequest &req) override;
    virtual void OnGetStringCheckMasterPass(const phxqueue::comm::proto::GetStringRequest &req) override;

    virtual void OnSetString(const phxqueue::comm::proto::SetStringRequest &req) override;
    virtual void OnSetStringRequestInvalid(const phxqueue::comm::proto::SetStringRequest &req) override;
    virtual void OnSetStringCheckMasterPass(const phxqueue::comm::proto::SetStringRequest &req) override;

    virtual void OnDeleteString(const phxqueue::comm::proto::DeleteStringRequest &req) override;
    virtual void OnDeleteStringRequestInvalid(const phxqueue::comm::proto::DeleteStringRequest &req) override;
    virtual void OnDeleteStringCheckMasterPass(const phxqueue::comm::proto::DeleteStringRequest &req) override;

    virtual void OnGetLockInfo(const phxqueue::comm::proto::GetLockInfoRequest &req) override;
    virtual void OnGetLockInfoRequestInvalid(const phxqueue::comm::proto::GetLockInfoRequest &req) override;
    virtual void OnGetLockInfoCheckMasterPass(const phxqueue::comm::proto::GetLockInfoRequest &req) override;

    virtual void OnAcquireLock(const phxqueue::comm::proto::AcquireLockRequest &req) override;
    virtual void OnAcquireLockRequestInvalid(const phxqueue::comm::proto::AcquireLockRequest &req) override;
    virtual void OnAcquireLockCheckMasterPass(const phxqueue::comm::proto::AcquireLockRequest &req) override;
};


class SKLockMgrBP : public phxqueue::comm::LockMgrBP {
  public:
    SKLockMgrBP() : phxqueue::comm::LockMgrBP() {}
    virtual ~SKLockMgrBP() override {}

    virtual void OnReadCheckpoint(const int topic_id, const uint32_t i) override;
    virtual void OnWriteCheckpoint(const int topic_id, const uint32_t i,
                                   uint64_t const checkpoint) override;

    virtual void OnReadRestartCheckpoint(const int topic_id, const uint32_t i) override;
    virtual void OnWriteRestartCheckpoint(const int topic_id, const uint32_t i,
                                          uint64_t const checkpoint) override;
};


class SKLockDbBP : public phxqueue::comm::LockDbBP {
  public:
    SKLockDbBP() : phxqueue::comm::LockDbBP() {}
    virtual ~SKLockDbBP() override {}

    virtual void OnVersionSetString(const bool sync);
    virtual void OnVersionDeleteString(const bool sync);
    virtual void OnAcquireLock(const bool sync) override;
};


class SKLockCleanThreadBP : public phxqueue::comm::LockCleanThreadBP {
  public:
    SKLockCleanThreadBP() : phxqueue::comm::LockCleanThreadBP() {}
    virtual ~SKLockCleanThreadBP() override {}

    virtual void OnProposeCleanSucc(const int topic_id, const int paxos_group_id) override;
    virtual void OnProposeCleanErr(const int topic_id, const int paxos_group_id) override;

    virtual void OnNrKey(const int topic_id, const int nr) override;
    virtual void OnNrCleanKey(const int topic_id, const int nr) override;
};


class SKLockKeepMasterThreadBP : public phxqueue::comm::LockKeepMasterThreadBP {
  public:
    SKLockKeepMasterThreadBP() : phxqueue::comm::LockKeepMasterThreadBP() {}
    virtual ~SKLockKeepMasterThreadBP() override {}

    virtual void OnProposeMasterSucc(const int topic_id, const int paxos_group_id) override;
    virtual void OnProposeMasterErr(const int topic_id, const int paxos_group_id) override;
};


class SKLockIMMasterBP : public phxqueue::comm::LockIMMasterBP {
  public:
    SKLockIMMasterBP() : phxqueue::comm::LockIMMasterBP() {}
    virtual ~SKLockIMMasterBP() override {}

    virtual void OnIMMaster(const int topic_id, const int paxos_group_id) override;
};


class SKLockSnatchMasterBP : public phxqueue::comm::LockSnatchMasterBP {
  public:
    SKLockSnatchMasterBP() : phxqueue::comm::LockSnatchMasterBP() {}
    virtual ~SKLockSnatchMasterBP() override {}

    virtual void OnSnatchMaster(const int topic_id, const int paxos_group_id) override;
};


class SKLockSMBP : public phxqueue::comm::LockSMBP {
  public:
    SKLockSMBP() : phxqueue::comm::LockSMBP() {}
    virtual ~SKLockSMBP() override {}

    virtual void OnExecute(const int topic_id, const int paxos_group_id,
                           const uint64_t instance_id, const std::string &paxos_value) override;
    virtual void OnExecuteForCheckpoint(const int topic_id, const int paxos_group_id,
                                        const uint64_t instance_id,
                                        const std::string &paxos_value) override;
    virtual void OnExecuteForCheckpointSync(const int topic_id, const int paxos_group_id,
                                            const uint64_t instance_id,
                                            const std::string &paxos_value) override;
    virtual void OnExecuteForCheckpointNoSync(const int topic_id, const int paxos_group_id,
                                              const uint64_t instance_id,
                                              const std::string &paxos_value) override;
    virtual void OnGetCheckpointInstanceID(const int topic_id, const int paxos_group_id) override;
    virtual void OnGetCheckpointState(const int topic_id, const int paxos_group_id) override;
    virtual void OnLoadCheckpointState(const int topic_id, const int paxos_group_id) override;
};


}  // namespace comm

}  // namespace skphxqueue

