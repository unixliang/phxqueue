from mm_envs import *

cc_library(
    target_bases = [ 'mmcomm', ],
    name = 'lock',
    srcs = [
        'sklock.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/plugin:plugin',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/phxqueue/lock:lock',
        '//comm2/core:core',
        '//comm2/svrkit:svrkit_cm',
        '//comm2/svrkit:svrkitepoll',
        '//mmcomm/mmsection2pb:mmsection2pb',
    ],
    optimize = [
        'O2',
    ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ],
)

