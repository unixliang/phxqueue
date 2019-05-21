
cc_library(
    name = "plugin",
    srcs = [
        "breakpointfactory.cpp",
        "configfactory.cpp",
        "logger_google.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/comm:comm_proto",
        "//phxqueue/phxqueue/config:config_proto",
        "//mm3rd/glog:glog",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)

