
cc_library(
    name = "utils",
    srcs = [
        "addr_util.cpp",
        "benchmark_util.cpp",
        "co_util.cpp",
        "consumer_group_util.cpp",
        "file_util.cpp",
        "hash_util.cpp",
        "load_util.cpp",
        "memory_util.cpp",
        "other_util.cpp",
        "string_util.cpp",
        "time_util.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/comm:comm_proto",
        "//basic/colib:colib",
    ],
    copts = [
        "-std=c++11",
        "-Wno-implicit-fallthrough",
    ],
    linkopts = [
        "-lpthread",
    ],
    visibility = ["//visibility:public"],
)

