from mm_envs import *

proto_library(
        name = 'config_proto',
        srcs = [
            'proto/globalconfig.proto',
            'proto/topicconfig.proto',
            'proto/consumerconfig.proto',
            'proto/storeconfig.proto',
            'proto/schedulerconfig.proto',
            'proto/lockconfig.proto',
        ],
        deps = [
            '//phxqueue:include',
            '//phxqueue/phxqueue/comm:comm_proto',
        ],
        prefix = "phxqueue",
)

cc_library(
    target_bases = [ 'mmcomm', ],
    name = 'config',
    srcs = [
        'consumerconfig.cpp',
        'globalconfig.cpp',
        'lockconfig.cpp',
        'schedulerconfig.cpp',
        'storeconfig.cpp',
        'topicconfig.cpp',
        'utils/pub_util.cpp',
        'utils/consumer_group_util.cpp',
        #'proto/consumerconfig.pb.cc',
        #'proto/globalconfig.pb.cc',
        #'proto/lockconfig.pb.cc',
        #'proto/schedulerconfig.pb.cc',
        #'proto/storeconfig.pb.cc',
        #'proto/topicconfig.pb.cc',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/phxqueue/comm:comm',
        '//phxqueue/phxqueue/plugin:plugin',
        ':config_proto',
    ],
    export_incs = [ '.', ],
    optimize = [
        'O2',
    ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)

