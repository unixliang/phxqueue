from mm_envs import *

proto_library(
    name = 'store_proto',
    srcs = [
        "proto/store.proto",
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/phxqueue/comm:comm_proto',
    ],
    prefix = "phxqueue",
)

cc_library(
    target_bases = [ 'mmcomm', ],
    name = 'store',
    srcs = [
        #'proto/store.pb.cc',
        'store.cpp',
        'basemgr.cpp',
        'syncctrl.cpp',
        'checkpointstat.cpp',
        'keepmasterthread.cpp',
        'keepsyncthread.cpp',
        'storemeta.cpp',
        'storesm.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/phxqueue/comm:comm',
        '//phxqueue/phxqueue/config:config',
        '//phxpaxos/plugin/include:include',
        '//phxpaxos/plugin:phxpaxos_plugin',
        '//phxpaxos:phxpaxos',
        ':store_proto',
        '#rt',
        '#z',
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

