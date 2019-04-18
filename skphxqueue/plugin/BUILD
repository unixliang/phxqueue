from mm_envs import *

cc_library(
    name = 'plugin',
    srcs = [
        'skbreakpointfactory.cpp',
        'skconfigfactory.cpp',
        'sklogger.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/config:config',
        '//comm2/core:core',
        '//mmcomm/mmsection2pb:mmsection2pb',
    ],
    export_incs = [ '.' ],
    optimize = [
        'O2',
    ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
		'-Wno-implicit-fallthrough',
    ],
)


