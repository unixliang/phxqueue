from mm_envs import *


cc_library(
    target_bases = [ 'mmcomm', ],
    name = 'producer',
    srcs = [
        'skproducer.cpp',
        'skselector.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/plugin:plugin',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/phxqueue/producer:producer',
        '//comm2/core:core',
        '//comm2/svrkit:svrkit_cm',
        '//comm2/svrkit:svrkitepoll',
        '//mmcomm/mmsection2pb:mmsection2pb',
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

