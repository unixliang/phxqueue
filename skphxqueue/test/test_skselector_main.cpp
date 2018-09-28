#include <iostream>

#include "iLog.h"

#include "skphxqueue/comm.h"
#include "skphxqueue/producer.h"
#include "skphxqueue/plugin.h"

using namespace skphxqueue;
using namespace std;

void ShowUsage(const char *proc) {
    printf("\t%s -t <topic_id> -p <pub_id> -u <uin> [-r](retry_switch_store)\n", proc);
}

int main(int argc, char **argv) {
    int topic_id = -1;
    int pub_id = -1;
    uint64_t uin = -1;
    bool retry_switch_store = 0;

    for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], "--help") == 0) {
			ShowUsage(argv[0]);
			return 0;
		} else if (strcmp(argv[i], "-t") == 0) {
            topic_id = std::atoi(argv[++i]);
            continue;
        } else if (strcmp(argv[i], "-p") == 0) {
            pub_id = std::atoi(argv[++i]);
            continue;
        }  else if (strcmp(argv[i], "-u") == 0) {
            uin = std::atoi(argv[++i]);
            continue;
        } else if (strcmp(argv[i], "-r") == 0) {
            retry_switch_store = true;
            continue;
        }
    }

    if (-1 == topic_id || -1 == pub_id) {
        ShowUsage(argv[0]);
        return 0;
    }

    Comm::OpenLog("test_skselector", 3, "/home/qspace/log");
    SetLogThreadMode(Comm::COMM_LOG_TM_ENABLE);

    phxqueue::plugin::ConfigFactory::SetConfigFactoryCreateFunc([]()->unique_ptr<phxqueue::plugin::ConfigFactory> {
            auto cf = new skphxqueue::plugin::SKConfigFactory("/home/qspace/etc/client/global/mmidcphxqueueglobal.conf");
            return unique_ptr<phxqueue::plugin::ConfigFactory>(cf);
        });

    phxqueue::comm::Logger::GetInstance()->SetLogFunc(plugin::SKLogger::GetLogger());


    producer::SKStoreSelectorDefault selector(topic_id, pub_id, uin, retry_switch_store);
    int store_id = -1;
    for (int i = 0; i < 3; ++i) {
        phxqueue::comm::RetCode ret = selector.GetStoreID(store_id);
        printf("%d %d\n", as_integer(ret), store_id);
    }

    return 0;
}
