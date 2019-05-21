
cc_binary(
    name = "test_config_main",
    srcs = [
        "test_config_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/plugin:plugin",
        "//phxqueue/phxqueue/test:test_config",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_binary(
    name = "test_consumer_main",
    srcs = [
        "test_consumer_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/plugin:plugin",
        "//phxqueue/phxqueue/test:simpleconsumer",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_binary(
    name = "test_producer_main",
    srcs = [
        "test_producer_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/plugin:plugin",
        "//phxqueue/phxqueue/test:simpleproducer",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
        "-ldl",
    ],
)


cc_binary(
    name = "test_store_main",
    srcs = [
        "test_store_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/store:store",
        "//phxqueue/phxqueue/plugin:plugin",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
        "-ldl",
    ],
)


cc_binary(
    name = "test_scheduler_main",
    srcs = [
        "test_scheduler_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/plugin:plugin",
        "//phxqueue/phxqueue/test:simplescheduler",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_binary(
    name = "test_lock_main",
    srcs = [
        "test_lock_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/lock:lock",
        "//phxqueue/phxqueue/plugin:plugin",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_library(
    name = "test_config",
    srcs = [
        "test_config.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/config:config",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "check_config",
    srcs = [
        "check_config.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/config:config",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "simpleconsumer",
    srcs = [
        "simpleconsumer.cpp",
        "simplehandler.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/config:config",
        "//phxqueue/phxqueue/consumer:consumer",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "simpleproducer",
    srcs = [
        "simpleproducer.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/producer:producer",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "simplescheduler",
    srcs = [
        "simplescheduler.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/scheduler:scheduler",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_binary(
    name = "test_plugin_main",
    srcs = [
        "test_plugin_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue/phxqueue/test:test_configfactory",
        "//phxqueue/phxqueue/test:test_log",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_library(
    name = "test_configfactory",
    srcs = [
        "test_configfactory.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/plugin:plugin",
        "//phxqueue/phxqueue/comm:comm",
        "//phxqueue/phxqueue/config:config",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "test_log",
    srcs = [
        "test_log.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/plugin:plugin",
        "//phxqueue/phxqueue/comm:comm",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_binary(
    name = "test_notifierpool_main",
    srcs = [
        "test_notifierpool_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/plugin:plugin",
        "//phxqueue/phxqueue/comm:comm",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
        "-ldl",
    ],
)


cc_binary(
    name = "test_get_queues_by_pub_id_main",
    srcs = [
        "test_get_queues_by_pub_id_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/plugin:plugin",
        "//phxqueue/phxqueue/comm:comm",
        "//phxqueue/phxqueue/config:config",
        "//phxqueue/phxqueue/consumer:consumer",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_binary(
    name = "test_consistent_hash_main",
    srcs = [
        "test_consistent_hash_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/plugin:plugin",
        "//phxqueue/phxqueue/comm:comm",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)

