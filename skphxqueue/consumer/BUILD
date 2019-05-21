
cc_library(
    name = "consumer",
    srcs = [
        "skconsumer.cpp",
        "skconsumercallgraphhelper.cpp",
        "skconsumerinithelper.cpp",
        "skconsumerserverconfig.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/plugin:plugin",
        "//phxqueue/phxqueue/consumer:consumer",
        "//comm2/core:core",
        "//comm2/svrkit:svrkit_cm",
        "//comm2/svrkit:svrkitepoll",
        "//mmcomm/mmsection2pb:mmsection2pb",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)

