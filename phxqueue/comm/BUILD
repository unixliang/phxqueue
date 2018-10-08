from mm_envs import *

proto_library(
    name = 'comm_proto',
    srcs = [
        "proto/comm.proto",
    ],
    deps = [
        '//phxqueue:include',
    ],
    prefix = "phxqueue",
)

cc_library(
    name = 'comm',
    srcs = [
        #'proto/comm.pb.cc',
        'breakpoint.cpp',
        'masterclient.cpp',
        'multiproc.cpp',
        'logger.cpp',
        'notifierpool.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/phxqueue/plugin:plugin',
        '//mm3rd/protobuf:protobuf',
        '//phxqueue/phxqueue/comm/utils:utils',
        ':comm_proto',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)
