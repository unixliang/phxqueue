from mm_envs import *

phxqueue_protoc_cmd = "cd %s; %s/mm3rd/protobuf/bin/protoc " \
        " --cpp_out=. -I. -I%s/mm3rd/protobuf/src/ " \
        "phxqueue/comm/proto/comm.proto " \
        "phxqueue/config/proto/globalconfig.proto " \
        "phxqueue/config/proto/topicconfig.proto " \
        "phxqueue/config/proto/consumerconfig.proto " \
        "phxqueue/config/proto/storeconfig.proto " \
        "phxqueue/config/proto/schedulerconfig.proto " \
        "phxqueue/config/proto/lockconfig.proto " \
        "phxqueue/lock/proto/lock.proto " \
        "phxqueue/store/proto/store.proto " \
        % (SRC_DIR(), BLADE_ROOT(), BLADE_ROOT())

gen_rule(
        name = 'phxqueue_proto',
        cmd = phxqueue_protoc_cmd,
        srcs = [
            'phxqueue/comm/proto/comm.proto',
            'phxqueue/config/proto/globalconfig.proto',
            'phxqueue/config/proto/topicconfig.proto',
            'phxqueue/config/proto/consumerconfig.proto',
            'phxqueue/config/proto/storeconfig.proto',
            'phxqueue/config/proto/schedulerconfig.proto',
            'phxqueue/config/proto/lockconfig.proto',
            'phxqueue/lock/proto/lock.proto',
            'phxqueue/store/proto/store.proto',
        ],
        outs = [
            'phxqueue/comm/proto/comm.pb.cc',
            'phxqueue/config/proto/globalconfig.pb.cc',
            'phxqueue/config/proto/topicconfig.pb.cc',
            'phxqueue/config/proto/consumerconfig.pb.cc',
            'phxqueue/config/proto/storeconfig.pb.cc',
            'phxqueue/config/proto/schedulerconfig.pb.cc',
            'phxqueue/config/proto/lockconfig.pb.cc',
            'phxqueue/lock/proto/lock.pb.cc',
            'phxqueue/store/proto/store.pb.cc',
        ],
)

skphxqueue_protoc_cmd = "cd %s; %s/mm3rd/protobuf/bin/protoc " \
        " --cpp_out=. -I. -I%s/mm3rd/protobuf/src/ " \
        "skphxqueue/comm/proto/skossconfig.proto " \
        "skphxqueue/config/proto/sklockconfig.proto " \
        "skphxqueue/config/proto/skstoreconfig.proto " \
        % (SRC_DIR(), BLADE_ROOT(), BLADE_ROOT())

gen_rule(
        name = 'skphxqueue_proto',
        cmd = skphxqueue_protoc_cmd,
        srcs = [
            'skphxqueue/comm/proto/skossconfig.proto',
            'skphxqueue/config/proto/sklockconfig.proto',
            'skphxqueue/config/proto/skstoreconfig.proto',
        ],
        outs = [
            'skphxqueue/comm/proto/skossconfig.pb.cc',
            'skphxqueue/config/proto/sklockconfig.pb.cc',
            'skphxqueue/config/proto/skstoreconfig.pb.cc',
        ],
)



cc_library(
    name = 'include',
    deps = [
         ':phxqueue_proto',
         ':skphxqueue_proto',
         '//mm3rd/protobuf:protobuf',
    ],
    export_incs = [ '.' ],
    incs = [ 'phxqueue', 'phxqueue_phxrpc'],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ],
)


    
