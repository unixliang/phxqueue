from mm_envs import *

cc_library(
    name = 'comm',
    srcs = [
        'proto/skossconfig.pb.cc',
        'skbreakpoint.cpp',
        'skossconfig.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/phxqueue/comm:comm',
        '//mm3rd/protobuf:protobuf',
        '//comm2/core:core',
        '//mmcomm/mmsection2pb:mmsection2pb',
        '//phxqueue/skphxqueue/comm/utils:utils',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)
