load("/code_generator/sktools", "private_protoc")
private_protoc(
    name = "config_proto_gen_rule1",
    srcs = [
        "proto/sklockconfig.proto",
    ],
    outs = [
        "proto/sklockconfig.pb.cc",
        "proto/sklockconfig.pb.h",
    ],
    prefix = "phxqueue",
)
private_protoc(
    name = "config_proto_gen_rule2",
    srcs = [
        "proto/skstoreconfig.proto",
    ],
    outs = [
        "proto/skstoreconfig.pb.cc",
        "proto/skstoreconfig.pb.h",
    ],
    prefix = "phxqueue",
)

cc_library(
    name = "config_proto",
    srcs = [
        "proto/sklockconfig.pb.cc",
        "proto/skstoreconfig.pb.cc",
    ],
    hdrs = [
        "proto/sklockconfig.pb.h",
        "proto/skstoreconfig.pb.h",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//mm3rd/protobuf:protobuf",
    ],
    copts = [
        "-Iphxqueue/skphxqueue/config/proto",
    ] + select({
        "//code_generator:is_protobuf_cpp11" : ["-std=c++11", ],
        "//conditions:default" : [],
    }),
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "config",
    srcs = [
        "skconsumerconfig.cpp",
        "sklockconfig.cpp",
        "skschedulerconfig.cpp",
        "skstoreconfig.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/phxqueue/config:config",
        "//comm2/core:core",
        "//mmcomm/mmsection2pb:mmsection2pb",
        "//phxqueue/skphxqueue/config:config_proto",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)

