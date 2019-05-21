load("/code_generator/sktools", "private_protoc")

cc_library(
    name = "include",
    srcs = [
    ],
    hdrs = [
        "proto/consumerconfig.pb.h",
        "proto/globalconfig.pb.h",
        "proto/lockconfig.pb.h",
        "proto/schedulerconfig.pb.h",
        "proto/storeconfig.pb.h",
        "proto/topicconfig.pb.h",
    ],
    includes = ['.'],
    deps = [
    ],
    copts = [
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)

private_protoc(
    name = "config_proto_gen_rule1",
    srcs = [
        "proto/globalconfig.proto",
    ],
    outs = [
        "proto/globalconfig.pb.cc",
        "proto/globalconfig.pb.h",
    ],
    prefix = "phxqueue",
)
private_protoc(
    name = "config_proto_gen_rule2",
    srcs = [
        "proto/topicconfig.proto",
    ],
    outs = [
        "proto/topicconfig.pb.cc",
        "proto/topicconfig.pb.h",
    ],
    prefix = "phxqueue",
)
private_protoc(
    name = "config_proto_gen_rule3",
    srcs = [
        "proto/consumerconfig.proto",
    ],
    outs = [
        "proto/consumerconfig.pb.cc",
        "proto/consumerconfig.pb.h",
    ],
    prefix = "phxqueue",
)
private_protoc(
    name = "config_proto_gen_rule4",
    srcs = [
        "proto/storeconfig.proto",
    ],
    outs = [
        "proto/storeconfig.pb.cc",
        "proto/storeconfig.pb.h",
    ],
    prefix = "phxqueue",
)
private_protoc(
    name = "config_proto_gen_rule5",
    srcs = [
        "proto/schedulerconfig.proto",
    ],
    outs = [
        "proto/schedulerconfig.pb.cc",
        "proto/schedulerconfig.pb.h",
    ],
    prefix = "phxqueue",
)
private_protoc(
    name = "config_proto_gen_rule6",
    srcs = [
        "proto/lockconfig.proto",
    ],
    outs = [
        "proto/lockconfig.pb.cc",
        "proto/lockconfig.pb.h",
    ],
    prefix = "phxqueue",
)

cc_library(
    name = "config_proto",
    srcs = [
        "proto/consumerconfig.pb.cc",
        "proto/globalconfig.pb.cc",
        "proto/lockconfig.pb.cc",
        "proto/schedulerconfig.pb.cc",
        "proto/storeconfig.pb.cc",
        "proto/topicconfig.pb.cc",
    ],
    hdrs = [
        "proto/consumerconfig.pb.h",
        "proto/globalconfig.pb.h",
        "proto/lockconfig.pb.h",
        "proto/schedulerconfig.pb.h",
        "proto/storeconfig.pb.h",
        "proto/topicconfig.pb.h",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/comm:comm_proto",
        "//mm3rd/protobuf:protobuf",
    ],
    copts = [
        "-Iphxqueue/phxqueue/config/proto",
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
        "consumerconfig.cpp",
        "globalconfig.cpp",
        "lockconfig.cpp",
        "schedulerconfig.cpp",
        "storeconfig.cpp",
        "topicconfig.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/comm:comm",
        "//phxqueue/phxqueue/plugin:plugin",
        "//phxqueue/phxqueue/config:config_proto",
        "//phxqueue/phxqueue/config/utils:utils",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)

