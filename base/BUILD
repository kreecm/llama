cc_library(
    name = "base",
    deps = [
        ":type",
	":value",
    ],
)

cc_library(
    name = "type",
    hdrs = [
        "math.h",
        "numeric_type.h",
        "type.h",
    ],
    srcs = [
        "numeric_type.cc",
        "type.cc",
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
    name = "numeric_type_test",
    srcs = ["numeric_type_test.cc"],
    deps = [
        ":type",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
