load("/code_generator/sktools", "private_protoc")
private_protoc(
    name = "comm_proto_gen_rule1",
    srcs = [
        "proto/comm.proto",
    ],
    outs = [
        "proto/comm.pb.cc",
        "proto/comm.pb.h",
    ],
    prefix = "phxqueue",
)

cc_library(
    name = "comm_proto",
    srcs = [
        "proto/comm.pb.cc",
    ],
    hdrs = [
        "proto/comm.pb.h",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//mm3rd/protobuf:protobuf",
    ],
    copts = [
        "-Iphxqueue/phxqueue/comm/proto",
    ] + select({
        "//code_generator:is_protobuf_cpp11" : ["-std=c++11", ],
        "//conditions:default" : [],
    }),
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "comm",
    srcs = [
        "breakpoint.cpp",
        "logger.cpp",
        "masterclient.cpp",
        "multiproc.cpp",
        "notifierpool.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/plugin:plugin",
        "//mm3rd/protobuf:protobuf",
        "//phxqueue/phxqueue/comm/utils:utils",
        "//phxqueue/phxqueue/comm:comm_proto",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)

