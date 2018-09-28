#include "skphxqueue/consumer/skconsumerserverconfig.h"

#include "iFileFunc.h"

#include "mmsection2pb.h"


namespace skphxqueue {

namespace consumer {


using namespace Comm;


SKConsumerServerConfig::SKConsumerServerConfig() {
    m_poConfig = new Comm::CEpollServerConfig;

    memset(topic_, 0, sizeof(topic_));
    shm_key_base_ = 0;
    log_level_ = 0;
    proc_num_ = 0;
    memset(proc_pid_path_, 0, sizeof(proc_pid_path_));
    memset(lock_path_base_, 0, sizeof(lock_path_base_));
    memset(phxqueue_global_config_path_, 0, sizeof(phxqueue_global_config_path_));
    memset(phxqueue_oss_config_path_, 0, sizeof(phxqueue_oss_config_path_));
}


int SKConsumerServerConfig::ReadConfig(const char *file) {
    MMERR("here. config_file %s", file);

    if(!file) {
        return -1;
    }

    int ret=0;

    ret = m_poConfig->Read(file);

    {
        CConfig config(file);
        ret = config.Init();
        if (0 == ret) {
            ConfigItemInfoEx_t infoArray[]{
                CONFIG_ITEM_EX_STR("General", "Topic", topic_, ""),

                CONFIG_ITEM_EX_INT("General", "ShmKeyBase", shm_key_base_, "18854"),
                CONFIG_ITEM_EX_STR("General", "LockPathBase", lock_path_base_, "/phxqueueconsumer.lock."),

                CONFIG_ITEM_EX_INT("General", "LogLevel", log_level_, "2"),
                CONFIG_ITEM_EX_STR("General", "ProcPidPath", proc_pid_path_, "/home/qspace/sbin/"),

                CONFIG_ITEM_EX_INT("General", "NProcs", proc_num_, "100"),

                CONFIG_ITEM_EX_STR("General", "PhxQueueGlobalConfigPath", phxqueue_global_config_path_, ""),
                CONFIG_ITEM_EX_STR("General", "PhxQueueOssConfigPath", phxqueue_oss_config_path_, ""),

                CONFIG_ITEM_EX_END
            };

            string cmdb_module_name;
            config.ReadItem("Server", "CmdbModuleName", "", cmdb_module_name);

            std::vector<std::string> tSuffixArray;
            ret = Comm::CEpollServerConfig::GetDeviceSuffix(&tSuffixArray, cmdb_module_name.c_str());
            if (0 != ret)
            {
                MMERR("ERR: GetDeviceSuffix ret %d", ret);
                return ret;
            }


            Comm::ConfigRead(&config, infoArray, &tSuffixArray);

            Comm::ConfigDump(infoArray);
        }
    }

    if (ret) MMERR("err. ret %d", ret);
    return ret;
}


}  // namespace consumer

}  // namespace skphxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

