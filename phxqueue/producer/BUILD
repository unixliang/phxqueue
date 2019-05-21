
cc_library(
    name = "producer",
    srcs = [
        "batchhelper.cpp",
        "producer.cpp",
        "selector.cpp",
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
        "-lrt",
        "-lz",
    ],
    visibility = ["//visibility:public"],
)

