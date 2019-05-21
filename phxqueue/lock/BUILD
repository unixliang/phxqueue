load("/code_generator/sktools", "private_protoc")
private_protoc(
    name = "lock_proto_gen_rule1",
    srcs = [
        "proto/lock.proto",
    ],
    outs = [
        "proto/lock.pb.cc",
        "proto/lock.pb.h",
    ],
    prefix = "phxqueue",
)

cc_library(
    name = "lock_proto",
    srcs = [
        "proto/lock.pb.cc",
    ],
    hdrs = [
        "proto/lock.pb.h",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/comm:comm_proto",
        "//mm3rd/protobuf:protobuf",
    ],
    copts = [
        "-Iphxqueue/phxqueue/lock/proto",
    ] + select({
        "//code_generator:is_protobuf_cpp11" : ["-std=c++11", ],
        "//conditions:default" : [],
    }),
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "lock",
    srcs = [
        "cleanthread.cpp",
        "keepmasterthread.cpp",
        "lock.cpp",
        "lockdb.cpp",
        "lockmgr.cpp",
        "locksm.cpp",
        "lockutils.cpp",
    ],
    hdrs = [
        "locksm.h",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/comm:comm",
        "//phxqueue/phxqueue/config:config",
        "//mm3rd/leveldb:leveldb",
        "//phxpaxos:phxpaxos",
        "//phxpaxos/plugin/include:include",
        "//phxpaxos/plugin:phxpaxos_plugin",
        "//phxpaxos/skplugin/include:include",
        "//phxpaxos/skplugin:phxpaxos_skplugin",
        "//phxqueue/phxqueue/lock:lock_proto",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)

