load("/code_generator/sktools", "private_protoc")
private_protoc(
    name = "store_proto_gen_rule1",
    srcs = [
        "proto/store.proto",
    ],
    outs = [
        "proto/store.pb.cc",
        "proto/store.pb.h",
    ],
    prefix = "phxqueue",
)

cc_library(
    name = "store_proto",
    srcs = [
        "proto/store.pb.cc",
    ],
    hdrs = [
        "proto/store.pb.h",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/comm:comm_proto",
        "//mm3rd/protobuf:protobuf",
    ],
    copts = [
        "-Iphxqueue/phxqueue/store/proto",
    ] + select({
        "//code_generator:is_protobuf_cpp11" : ["-std=c++11", ],
        "//conditions:default" : [],
    }),
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "store",
    srcs = [
        "basemgr.cpp",
        "checkpointstat.cpp",
        "keepmasterthread.cpp",
        "keepsyncthread.cpp",
        "store.cpp",
        "storemeta.cpp",
        "storesm.cpp",
        "syncctrl.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/comm:comm",
        "//phxqueue/phxqueue/config:config",
        "//phxpaxos/plugin/include:include",
        "//phxpaxos/plugin:phxpaxos_plugin",
        "//phxpaxos:phxpaxos",
        "//phxqueue/phxqueue/store:store_proto",
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

