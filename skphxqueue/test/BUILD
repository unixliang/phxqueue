
cc_binary(
    name = "test_skconsumer_main",
    srcs = [
        "test_skconsumer_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//comm2/core:core",
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/config:config",
        "//phxqueue/skphxqueue/plugin:plugin",
        "//phxqueue/skphxqueue/test:sksimpleconsumer",
        "//phxqueue/skphxqueue/test:sksimplehandler",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_binary(
    name = "test_skscheduler_main",
    srcs = [
        "test_skscheduler_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/config:config",
        "//phxqueue/skphxqueue/plugin:plugin",
        "//phxqueue/skphxqueue/test:sksimplescheduler",
        "//comm2/core:core",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_binary(
    name = "test_sklock_main",
    srcs = [
        "test_sklock_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/config:config",
        "//phxqueue/skphxqueue/plugin:plugin",
        "//phxqueue/skphxqueue/lock:lock",
        "//comm2/core:core",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_library(
    name = "sksimpleconsumer",
    srcs = [
        "sksimpleconsumer.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/config:config",
        "//phxqueue/skphxqueue/consumer:consumer",
        "//phxqueue/skphxqueue/plugin:plugin",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "sksimplehandler",
    srcs = [
        "sksimplehandler.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/phxqueue/comm:comm",
        "//phxqueue/skphxqueue/config:config",
        "//comm2/core:core",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "sksimplescheduler",
    srcs = [
        "sksimplescheduler.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/config:config",
        "//phxqueue/skphxqueue/scheduler:scheduler",
        "//phxqueue/skphxqueue/plugin:plugin",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_binary(
    name = "test_skbreakpoint_main",
    srcs = [
        "test_skbreakpoint_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/config:config",
        "//phxqueue/skphxqueue/plugin:plugin",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_binary(
    name = "test_skconfig_main",
    srcs = [
        "test_skconfig_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue/skphxqueue/test:test_skconfig",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_library(
    name = "test_skconfig",
    srcs = [
        "test_skconfig.cpp",
    ],
    hdrs = [
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/config:config",
        "//phxqueue/skphxqueue/plugin:plugin",
        "//phxqueue/phxqueue/test:test_config",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
    visibility = ["//visibility:public"],
)


cc_binary(
    name = "skconfig_check_main",
    srcs = [
        "skconfig_check_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/config:config",
        "//phxqueue/skphxqueue/plugin:plugin",
        "//phxqueue/phxqueue/test:check_config",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)


cc_binary(
    name = "test_skselector_main",
    srcs = [
        "test_skselector_main.cpp",
    ],
    includes = ['.'],
    deps = [
        "//comm2/core:core",
        "//phxqueue:include",
        "//phxqueue/skphxqueue/comm:comm",
        "//phxqueue/skphxqueue/config:config",
        "//phxqueue/skphxqueue/plugin:plugin",
        "//phxqueue/skphxqueue/producer:producer",
    ],
    copts = [
        "-std=c++11",
    ],
    linkopts = [
    ],
)

