from mm_envs import *

proto_library(
    name = 'lock_proto',
    srcs = [
        "proto/lock.proto",
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/phxqueue/comm:comm_proto',
    ],
    prefix = "phxqueue",
)

cc_library(
    target_bases = [ 'mmcomm', ],
    name = 'lock',
    srcs = [
        #'proto/lock.pb.cc',
        'cleanthread.cpp',
        'keepmasterthread.cpp',
        'lock.cpp',
        'lockdb.cpp',
        'lockmgr.cpp',
        'locksm.cpp',
        'lockutils.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/phxqueue/comm:comm',
        '//phxqueue/phxqueue/config:config',
        '//mm3rd/leveldb:leveldb',
        '//phxpaxos:phxpaxos',
        '//phxpaxos/plugin/include:include',
        '//phxpaxos/plugin:phxpaxos_plugin',
        '//phxpaxos/skplugin/include:include',
        '//phxpaxos/skplugin:phxpaxos_skplugin',
        ':lock_proto',
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

