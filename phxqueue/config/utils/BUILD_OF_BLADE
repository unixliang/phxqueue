cc_library(
    name = 'utils',
    srcs = [
        'pub_util.cpp',
        'consumer_group_util.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/phxqueue/config:config_proto',
        '#pthread',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)
