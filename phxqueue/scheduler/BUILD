
cc_library(
    name = "scheduler",
    srcs = [
        "keepmasterthread.cpp",
        "loadbalancethread.cpp",
        "scheduler.cpp",
        "schedulermgr.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
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

