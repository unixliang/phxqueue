from mm_envs import *

proto_library(
        name = 'config_proto',
        srcs = [
            'proto/sklockconfig.proto',
            'proto/skstoreconfig.proto',
        ],
        deps = [
            '//phxqueue:include',
        ],
        prefix = "phxqueue",
)

cc_library(
    name = 'config',
    srcs = [
        #'proto/sklockconfig.pb.cc',
        #'proto/skstoreconfig.pb.cc',
        'skconsumerconfig.cpp',
        'sklockconfig.cpp',
        'skschedulerconfig.cpp',
        'skstoreconfig.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/phxqueue/config:config',
        '//comm2/core:core',
        '//mmcomm/mmsection2pb:mmsection2pb',
        ':config_proto',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)
