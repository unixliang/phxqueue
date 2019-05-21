
cc_library(
    name = "utils",
    srcs = [
        "consumer_group_util.cpp",
        "pub_util.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/config:config_proto",
        "//phxqueue/phxqueue/config:include",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
        "-lpthread",
    ],
    visibility = ["//visibility:public"],
)

