from mm_envs import *

cc_library(
    target_bases = [ 'mmcomm', ],
    name = 'store',
    srcs = [
        'skstore.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/plugin:plugin',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/phxqueue/store:store',
        '//comm2/core:core',
        '//comm2/svrkit:svrkit_cm',
        '//comm2/svrkit:svrkitepoll',
        '//mmcomm/mmsection2pb:mmsection2pb',
        '//phxpaxos/skplugin/include:include',
        '//phxpaxos/skplugin:phxpaxos_skplugin',
        '//phxpaxos:phxpaxos',
    ],
    optimize = [
        'O2',
    ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)

