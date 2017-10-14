cc_library(
    name = "base",
    deps = [
        ":type",
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
        
cc_test(
    name = "numeric_type_test",
    srcs = ["numeric_type_test.cc"],
    deps = [
        ":type",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
