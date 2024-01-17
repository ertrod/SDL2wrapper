
optional_defines = [
  "SDL2WRAPPER_IMAGE",
  "SDL2WRAPPER_FONT",
  "SDL2WRAPPER_MIXER",
]

cc_library(
  name = "sdl2wrapperlib",
  hdrs = glob(["SDL2wrapper/include/*.h"]),
  deps = [
    "@sdl//:sdl",
  ],
  defines = optional_defines,
  visibility = ["//visibility:public"],
)


cc_library(
  name = "sdl2wrapper",
  hdrs = glob(["SDL2wrapper/include/*.h"]),
  srcs = glob(["SDL2wrapper/src/*.cc"]),
  deps = [
    ":sdl2wrapperlib",
    "@sdl//:sdl",
  ],
  defines = optional_defines,
  visibility = ["//visibility:public"],
)