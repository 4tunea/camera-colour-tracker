cmake_minimum_required(VERSION 3.16)

project(
    camera_colour_tracker
    VERSION 0.1.0
    LANGUAGES CXX
)

add_executable(
    colour_tracker
    src/main.cpp
)

target_compile_features(
    colour_tracker
    PRIVATE
    cxx_std_20
)

target_compile_options(
    colour_tracker
    PRIVATE
    -Wall
    -Wextra
    -Wpendantic
)