#pragma once

#include <cstdlib>

#include "iFileFunc.h"


namespace Comm {


class CEpollServerConfig;


}


namespace skphxqueue {

namespace consumer {


class SKConsumerServerConfig {
  public:
    SKConsumerServerConfig();
    virtual ~SKConsumerServerConfig() {}
    int ReadConfig(const char *file = nullptr);

    const char *GetTopic() { return topic_; }

    int GetShmKeyBase() { return shm_key_base_; }

    int GetLogLevel() { return log_level_; }

    int GetNProcs() { return proc_num_; }

    const char *GetProcPidPath() { return proc_pid_path_; }

    const char *GetLockPathBase() { return lock_path_base_; }

    const char *GetPhxQueueGlobalConfigPath() { return phxqueue_global_config_path_; }

    const char *GetPhxQueueOssConfigPath() { return phxqueue_oss_config_path_; }

    Comm::CEpollServerConfig *GetEpollConfig() { return m_poConfig; }


  private:
    Comm::CEpollServerConfig *m_poConfig;

    char topic_[256];
    int shm_key_base_;
    int log_level_;
    int proc_num_;
    char proc_pid_path_[256];
    char lock_path_base_[256];
    char phxqueue_global_config_path_[256];
    char phxqueue_oss_config_path_[256];

};


}  // namespace consumer

}  // namespace skphxqueue

