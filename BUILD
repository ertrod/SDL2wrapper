load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "SDL2wrapper",
    defines = [
        "SDL2WRAPPER_IMAGE",
        "SDL2WRAPPER_FONT",
        "SDL2WRAPPER_MIXER",
    ],
    hdrs = glob(["include/*.h"]),
    srcs = glob(["src/*.cc"]),
    deps = [
        "//libs:sdl2"
    ],
    visibility = ["//visibility:public"],
)