cc_library(
    name = "base",
    deps = [
        ":type",
	":value",
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
        ":math",
    ],
)


cc_library(
    name = "value",
    hdrs = [
        "value.h",
    ],
    srcs = [
        "value.cc",
    ],
    deps = [
    	":type",
    ]
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
