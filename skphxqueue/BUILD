cc_library(
    name = 'skphxqueue',
    deps = [
        '//phxqueue/skphxqueue/include:include',
        '//phxqueue/skphxqueue/src/breakpoint:skbreakpoint',
        '//phxqueue/skphxqueue/src/config:skconfig',
        '//phxqueue/skphxqueue/src/consumer:skconsumer',
        '//phxqueue/skphxqueue/src/lock:sklock',
        '//phxqueue/skphxqueue/src/producer:skproducer',
        '//phxqueue/skphxqueue/src/scheduler:skscheduler',
        '//phxqueue/skphxqueue/src/store:skstore',
    ],
    export_incs = [ '.' ],
    optimize = [
        'O2',
    ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ],
)

