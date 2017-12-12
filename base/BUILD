cc_library(
    name = "base",
    deps = [
        ":type",
	":value",
    ],
)

#
# Libraries
# =============================================================================

cc_library(
    name = "error",
    hdrs = [
        "error.h",
        "error_code.h",
        "error_handler.h",
        "error_status.h",
    ],
    srcs = [
        "error_code.cc",
        "error_handler.cc",
        "error_status.cc",
    ],
)

cc_library(
    name = "math",
    hdrs = ["math.h"],
)

cc_library(
    name = "type",
    hdrs = [
        "numeric_type.h",
        "type.h",
    ],
    srcs = [
        "numeric_type.cc",
        "type.cc",
    ],
    deps = [
        ":error",
        ":math",
    ],
)


cc_library(
    name = "value",
    hdrs = [
        "value.h",
        "value_base.h",
        "value_ptr.h",
    ],
    srcs = [
        "value.cc",
    ],
    deps = [
    	":type",
    ]
)

#
# Tests
# =============================================================================

cc_test(
    name = "error_code_test",
    srcs = ["error_code_test.cc"],
    deps = [
        ":error",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "error_status_test",
    srcs = ["error_status_test.cc"],
    deps = [
        ":error",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "math_test",
    srcs = ["math_test.cc"],
    deps = [
        ":math",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "numeric_type_test",
    srcs = ["numeric_type_test.cc"],
    deps = [
        ":type",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "value_test",
    srcs = ["value_test.cc"],
    deps = [
        ":value",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
