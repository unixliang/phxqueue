#include "skphxqueue/consumer/skconsumer.h"

#include <sys/prctl.h>

#include <zlib.h>

#include "iFastReject.h"

#include "clsBatchUtils.h"
#include "clsFuncBind.h"
#include "mmlb_stat_helper.h"
#include "mmlbclient.h"
#include "oss_call_stat_helper.h"
#include "snappy.h"
#include "skmodulecallstack.h"

#include "phxqueue/comm.h"
#include "phxqueue/config.h"
#include "phxqueue/consumer.h"

#include "skphxqueue/comm.h"
#include "skphxqueue/consumer/skconsumercallgraphhelper.h"

namespace skphxqueue {

namespace consumer {


using namespace Comm;
using namespace std;


void SKConsumer::BeforeFork() {
    auto &&opt(GetConsumerOption());

    // for leshem
    int listenfd{SKEpollUtils::Listen(opt->port, 512, opt->ip.c_str())};
    if (listenfd < 0) {
        MMERR("ERR: Listen fail. return %d", listenfd);
        exit(-1);
    }

    // for connagent
    INIT_SKCOROUTINE

    // 调用关系 & mmlb 初始化
    MMLBClient::SetRouteStatusReportCallback();
    oss_call_stat_dict_at(Comm::GetLogModuleName());
    oss_call_stat_dict_at("unknown");
    oss_call_stat_run(2 * (opt->nprocs + 10), 0, 0);
    mmlb_stat_run(2 * (opt->nprocs + 10), 0);
    ModuleCallStack::InitLogCallStackFactory(2 * (opt->nprocs + 10), 0);

    QLVerb("init mmlb %d", 2 * (opt->nprocs + 10));

}

void SKConsumer::OnChildRun(const int vpid) {
    int ret;

    prctl(PR_SET_PDEATHSIG, SIGHUP);
    QLVerb("attach id %d", 2 * vpid);
    oss_call_stat_attach(2 * vpid);
    mmlb_stat_attach(2 * vpid);
    ModuleCallStack::AttachLogCallStack(2 * vpid);

    //InitFactory(1, 50, 1024 * 128); // 50 routines, 128kb stack

    // client fastreject
    if (0 != (ret = FastRejectQoSManager::GetDefault()->Init(NULL, false))) {
        MMERR("ERR: FastRejectQoSManager::Init ret %d", ret);
    }
}

void SKConsumer::OnRunSync() {
    auto &&opt(GetConsumerOption());

    const int vpid{opt->nprocs + 1};
    QLVerb("attach id %d", 2 * vpid);
    oss_call_stat_attach(2 * vpid);
    mmlb_stat_attach(2 * vpid);
    ModuleCallStack::AttachLogCallStack(2 * vpid);
}

void SKConsumer::OnConsumeThreadRun(const int vpid) {
    QLVerb("attach id %d", 2 * vpid + 1);
    oss_call_stat_attach(2 * vpid + 1);
    mmlb_stat_attach(2 * vpid + 1);
    ModuleCallStack::AttachLogCallStack(2 * vpid + 1);
}


void SKConsumer::BeforeLock(const phxqueue::comm::proto::ConsumerContext &cc) {
    static time_t fast_reject_last_check_time{0};
    auto now(time(nullptr));
    if (now >= fast_reject_last_check_time + 60) {
        fast_reject_last_check_time = now;
        if (FastRejectQoSManager::GetDefault()->IsInit()) {
            FastRejectQoSManager::GetDefault()->Reload(false, false);
        }
    }
}

void SKConsumer::BeforeGet(const phxqueue::comm::proto::GetRequest &req) {
    Comm::SetDyeLogInfoUin(Comm::GetRandomUin());
}


void SKConsumer::RestoreUserCookies(const phxqueue::comm::proto::Cookies &user_cookies) {
    OssAttrInc(59104, 9, 1);

    bool syscookie_ok = false;
    bool dyeloginfo_ok = false;

    // syscookie
    {
        for (size_t i{0}; i < user_cookies.cookies_size(); ++i) {
            auto &&cookie = user_cookies.cookies(i);

            if (cookie.key() == "syscookie") {
                OssAttrInc(59104, 10, 1);
                Comm::MMSystemReqCookie syscookie;
                if (syscookie.ParseFromString(cookie.val())) {
                    Comm::GetSysReqCookie()->Swap(&syscookie);
                    Comm::ConvertSysReqCookieToDyeLogInfo();
                    syscookie_ok = true;
                    OssAttrInc(59104, 11, 1);
                } else {
                    OssAttrInc(59104, 12, 1);
                }
            }
        }
    }

    // dyeloginfo
    if (!syscookie_ok) {
        for (size_t i{0}; i < user_cookies.cookies_size(); ++i) {
            auto &&cookie = user_cookies.cookies(i);

            if (cookie.key() == "dyeloginfo") {
                OssAttrInc(59104, 13, 1);
                Comm::SKBuffer buff;
                Comm::DyeLogInfo_t dyeloginfo;
                buff.Write(cookie.val().c_str(), cookie.val().size());
                if (Comm::SKFrmwCookie::DyeLogInfoFromBuffer(&buff, &dyeloginfo) == 0 &&
                    dyeloginfo.isDeliver) {
                    Comm::SetDyeLogInfo(dyeloginfo);
                    dyeloginfo_ok = true;
                    OssAttrInc(59104, 14, 1);
                } else {
                    OssAttrInc(59104, 15, 1);
                }
            }
        }
    }

    if (syscookie_ok || dyeloginfo_ok) {
        OssAttrInc(59104, 16, 1);

        skphxqueue::comm::utils::PrintCallGraphInfo();

        Comm::DyeLogInfo_t dyeloginfo;
        Comm::GetDyeLogInfo(&dyeloginfo);
        Comm::SetDyeLogLevel(dyeloginfo.logLevel);

        // fix call graph
        SKConsumerCallGraphHelper::GetInstance()->FixGraph();
    } else {
        OssAttrInc(59104, 17, 1);
    }
    Comm::OpenCacheLog();
}

phxqueue::comm::RetCode
SKConsumer::UncompressBuffer(const string &buffer, const int buffer_type,
                             string &uncompressed_buffer) {
    if (0 == buffer_type) {
        uncompressed_buffer = buffer;
        return phxqueue::comm::RetCode::RET_OK;
    } else if (1 == buffer_type){
        if (!snappy::Uncompress(buffer.c_str(), buffer.size(), &uncompressed_buffer)) {
            MMERR("ERR: Uncompress fail. buffer size %zu", buffer.size());
            return phxqueue::comm::RetCode::RET_ERR_UNCOMPRESS;
        }
        return phxqueue::comm::RetCode::RET_OK;
    }
    return phxqueue::comm::RetCode::RET_ERR_BUFFER_TYPE;
}

void SKConsumer::CompressBuffer(const string &buffer, string &compressed_buffer,
                                const int buffer_type) {
    if (0 == buffer_type) {
        compressed_buffer = buffer;
    } else if (1 == buffer_type) {
        snappy::Compress(buffer.c_str(), buffer.length(), &compressed_buffer);
    }
}

static size_t CalHash(const phxqueue::consumer::Queue_t &queue) {
    size_t h = crc32(0, Z_NULL, 0);
    h = crc32(h, (const unsigned char *)&queue.consumer_group_id, sizeof(int));
    h = crc32(h, (const unsigned char *)&queue.store_id, sizeof(int));
    h = crc32(h, (const unsigned char *)&queue.queue_id, sizeof(int));
    return h;
}

static size_t CalHashOld(const phxqueue::consumer::Queue_t &queue) {
    size_t h = crc32(0, Z_NULL, 0);
    h = crc32(h, (const unsigned char *)&queue.consumer_group_id, sizeof(int));
    h = crc32(h, (const unsigned char *)&queue.pub_id, sizeof(int));
    h = crc32(h, (const unsigned char *)&queue.store_id, sizeof(int));
    h = crc32(h, (const unsigned char *)&queue.queue_id, sizeof(int));
    return h;
}

static void ClearEndpointBucketVector(Comm::CEndpointBucketVector *buckets) {
    if (!buckets) return;
    Comm::CEndpointBucketVector::iterator it{buckets->begin()};
    for (; buckets->end() != it; ++it) {
        delete (*it);
    }
    buckets->clear();
    buckets->shrink_to_fit();
}

phxqueue::comm::RetCode
SKConsumer::GetQueueByAddrScale(const vector<phxqueue::consumer::Queue_t> &queues,
                                const phxqueue::consumer::AddrScales &addr_scales,
                                set<size_t> &queue_idxs) {

    phxqueue::comm::RetCode ret;
    int topic_id = GetTopicID();
    shared_ptr<const phxqueue::config::TopicConfig> topic_config;
    ret = phxqueue::config::GlobalConfig::GetThreadInstance()->
            GetTopicConfigByTopicID(topic_id, topic_config);
    if (phxqueue::comm::RetCode::RET_OK != ret) {
        MMERR("GetTopicConfigByTopicID ret %d topicid %d", phxqueue::comm::as_integer(ret), topic_id);
        return ret;
    }

    Comm::CBaseClientConfig cli_config;

    Comm::CEndpointBucketVector *buckets{cli_config.GetEndpointConfig()->GetList()};

    ClearEndpointBucketVector(buckets);

    for (auto &&addr_scale : addr_scales) {
        unique_ptr<Comm::CEndpointBucket> bucket{new Comm::CEndpointBucket()};
        unique_ptr<Comm::CEndpoint> ep{new Comm::CEndpoint()};
        ep->SetIP(addr_scale.addr().ip().c_str());
        ep->SetPort(addr_scale.addr().port());
        ep->SetScale(addr_scale.scale());
        ep->SetBeginSect(-1);
        ep->SetEndSect(-1);

        MMDEBUG("add ep(%s:%d) scale %d", ep->GetIP(), ep->GetPort(), ep->GetScale());

        bucket->SetBeginSect(-1);
        bucket->SetEndSect(-1);
        bucket->Add(ep.release());
        buckets->push_back(bucket.release());
    }

    auto &&opt(GetConsumerOption());
    for (size_t i{0}; i < queues.size(); ++i) {
        //auto hash = CalHash(queues[i]);
        auto hash(topic_config->GetProto().topic().use_new_hash() ? CalHash(queues[i]) : CalHashOld(queues[i]));
        Comm::CConfigCtx ctx;
        Comm::CEndpoint ep;
        cli_config.GetByHrwHash(hash, ctx, &ep);
        MMDEBUG("DEBUG: i %zu hash %zu ep(%s:%d) local_ip %s",
                i, hash, ep.GetIP(), ep.GetPort(), opt->ip.c_str());
        if (opt->ip == ep.GetIP()) {
            queue_idxs.insert(i);
        }
    }

    ClearEndpointBucketVector(buckets);

    MMDEBUG("DEBUG: queues.size %zu addrscales.size %zu queue_idxs.size %zu",
            queues.size(), addr_scales.size(), queue_idxs.size());

    return phxqueue::comm::RetCode::RET_OK;
}


}  // namespace consumer

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

