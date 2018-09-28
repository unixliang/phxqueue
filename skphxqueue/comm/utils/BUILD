cc_library(
    name = 'utils',
    srcs = [
        'callgraph_util.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//comm2/core:core',
        '//comm2/svrkit:svrkit_cm',
        '//comm2/svrkit:svrkitepoll',
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
