cc_binary(
    name = 'test_skconsumer_main',
    srcs = [
        'test_skconsumer_main.cpp',
    ],
    deps = [
        '//comm2/core:core',
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/skphxqueue/plugin:plugin',
        ':sksimpleconsumer',
        ':sksimplehandler',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)


cc_binary(
    name = 'test_skscheduler_main',
    srcs = [
        'test_skscheduler_main.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/skphxqueue/plugin:plugin',
        ':sksimplescheduler',
        '//comm2/core:core',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)


cc_binary(
    name = 'test_sklock_main',
    srcs = [
        'test_sklock_main.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/skphxqueue/plugin:plugin',
        '//phxqueue/skphxqueue/lock:lock',
        '//comm2/core:core',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)


cc_library(
    target_bases = [ 'mmcomm', ],
    name = 'sksimpleconsumer',
    srcs = [
        'sksimpleconsumer.cpp'
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/skphxqueue/consumer:consumer',
        '//phxqueue/skphxqueue/plugin:plugin',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)


cc_library(
    target_bases = [ 'mmcomm', ],
    name = 'sksimplehandler',
    srcs = [
        'sksimplehandler.cpp'
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/phxqueue/comm:comm',
        '//phxqueue/skphxqueue/config:config',
        '//comm2/core:core',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)

cc_library(
    target_bases = [ 'mmcomm', ],
    name = 'sksimplescheduler',
    srcs = [
        'sksimplescheduler.cpp'
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/skphxqueue/scheduler:scheduler',
        '//phxqueue/skphxqueue/plugin:plugin',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)











cc_binary(
    name = 'test_skbreakpoint_main',
    srcs = [
        'test_skbreakpoint_main.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/skphxqueue/plugin:plugin',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)

cc_binary(
    name = 'test_skconfig_main',
    srcs = [
        'test_skconfig_main.cpp',
    ],
    deps = [
        ':test_skconfig',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)


cc_library(
    target_bases = [ 'mmcomm', ],
    name = 'test_skconfig',
    srcs = [
        'test_skconfig.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/skphxqueue/plugin:plugin',
        '//phxqueue/phxqueue/test:test_config',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)




cc_binary(
    name = 'skconfig_check_main',
    srcs = [
        'skconfig_check_main.cpp',
    ],
    deps = [
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/skphxqueue/plugin:plugin',
        '//phxqueue/phxqueue/test:check_config',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)


cc_binary(
    name = 'test_skselector_main',
    srcs = [
        'test_skselector_main.cpp',
    ],
    deps = [
        '//comm2/core:core',
        '//phxqueue:include',
        '//phxqueue/skphxqueue/comm:comm',
        '//phxqueue/skphxqueue/config:config',
        '//phxqueue/skphxqueue/plugin:plugin',
        '//phxqueue/skphxqueue/producer:producer',
    ],
    export_incs = [ '.', ],
    extra_cppflags = [
        '-Wall',
        '-Werror',
        '-std=c++11',
    ]
)
