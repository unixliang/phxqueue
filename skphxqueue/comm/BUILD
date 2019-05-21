load("/code_generator/sktools", "private_protoc")
private_protoc(
    name = "comm_proto_gen_rule1",
    srcs = [
        "proto/skossconfig.proto",
    ],
    outs = [
        "proto/skossconfig.pb.cc",
        "proto/skossconfig.pb.h",
    ],
    prefix = "phxqueue",
)

cc_library(
    name = "comm_proto",
    srcs = [
        "proto/skossconfig.pb.cc",
    ],
    hdrs = [
        "proto/skossconfig.pb.h",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//mm3rd/protobuf:protobuf",
    ],
    copts = [
        "-Iphxqueue/skphxqueue/comm/proto",
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
        "skbreakpoint.cpp",
        "skossconfig.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/comm:comm",
        "//mm3rd/protobuf:protobuf",
        "//comm2/core:core",
        "//mmcomm/mmsection2pb:mmsection2pb",
        "//phxqueue/skphxqueue/comm/utils:utils",
        "//phxqueue/skphxqueue/comm:comm_proto",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)

