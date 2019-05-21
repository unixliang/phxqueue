
cc_library(
    name = "lock",
    srcs = [
        "sklock.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/plugin:plugin",
        "//phxqueue/skphxqueue/config:config",
        "//phxqueue/phxqueue/lock:lock",
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

