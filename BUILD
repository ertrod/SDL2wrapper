load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "SDL2wrapper",
    hdrs = glob(["include/*.h"]),
    srcs = glob(["src/*.cc"]),
    deps = [
        "//SDL:sdl2"
    ],
    defines = [
        "SDL2WRAPPER_IMAGE",
        "SDL2WRAPPER_FONT",
        "SDL2WRAPPER_MIXER",
    ],
    visibility = ["//visibility:public"],
)