from mm_envs import *

cc_library(
    name = 'config',
    srcs = [
        'proto/sklockconfig.pb.cc',
        'proto/skstoreconfig.pb.cc',
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
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)
