load("@rules_cc//cc:defs.bzl", "cc_test")

# cc_test(
#     name = "sdl2wrapper-test",
#     srcs =  glob(["*.cc"]),
#     deps = [
#         "@com_google_googletest//:gtest_main",
#         "//libs:sdl2",
#         "//SDL2wrapper:SDL2wrapper",
#     ],
# )

cc_test(
    name = "sdl2wrapper-point-test",
    srcs = ["sdl_point_test.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//libs:sdl2",
        "//SDL2wrapper:SDL2wrapper",
    ] 
)
cc_test(
    name = "sdl2wrapper-pointers-test",
    srcs = ["sdl_pointers_test.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//libs:sdl2",
        "//SDL2wrapper:SDL2wrapper",
    ] 
)
cc_test(
    name = "sdl2wrapper-color-test",
    srcs = ["sdl_color_test.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//libs:sdl2",
        "//SDL2wrapper:SDL2wrapper",
    ]
)
cc_test(
    name = "sdl2wrapper-rect-test",
    srcs = ["sdl_rectangle_test.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//libs:sdl2",
        "//SDL2wrapper:SDL2wrapper",
    ]
)
cc_test(
    name = "sdl2wrapper-surface-lock-test",
    srcs = ["sdl_surface_lock_test.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//libs:sdl2",
        "//SDL2wrapper:SDL2wrapper",
    ]
)
cc_test(
    name = "sdl2wrapper-surface-test",
    srcs = ["sdl_surface_test.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//libs:sdl2",
        "//SDL2wrapper:SDL2wrapper",
    ]
)
cc_test(
    name = "sdl2wrapper-window-test-live",
    srcs = ["sdl_window_test_live.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//libs:sdl2",
        "//SDL2wrapper:SDL2wrapper",
    ]
)
cc_test(
    name = "sdl2wrapper-renderer-test-live",
    srcs = ["sdl_renderer_test_live.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//libs:sdl2",
        "//SDL2wrapper:SDL2wrapper",
    ],
    data = ["testdata/crate.png"],
)
cc_test(
    name = "sdl2wrapper-font-test",
    srcs = ["sdl_font_test.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//libs:sdl2",
        "//SDL2wrapper:SDL2wrapper",
    ]
    data = ["testdata/Vera.ttf"]
)