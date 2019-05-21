
cc_library(
    name = "plugin",
    srcs = [
        "skbreakpointfactory.cpp",
        "skconfigfactory.cpp",
        "sklogger.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/config:config",
        "//comm2/core:core",
        "//mmcomm/mmsection2pb:mmsection2pb",
    ],
    copts = [
        "-std=c++11",
        "-Wno-implicit-fallthrough",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)

