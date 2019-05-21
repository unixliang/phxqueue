
cc_library(
    name = "consumer",
    srcs = [
        "consumer.cpp",
        "eventhandler.cpp",
        "freqman.cpp",
        "hblock.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/comm:comm",
        "//phxqueue/phxqueue/config/utils:utils",
        "//phxqueue/phxqueue/producer:producer",
        "//basic/colib:colib",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
        "-ldl",
        "-lrt",
        "-lz",
    ],
    visibility = ["//visibility:public"],
)

