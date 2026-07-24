cmake_minimum_required(VERSION 3.16)

project(
    camera_colour_tracker
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    colour_tracker
    src/main.cpp
)

find_package(OpenCV REQUIRED)

target_include_directories(
    colour_tracker
    PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    colour_tracker
    PRIVATE
    ${OpenCV_LIBS}
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
    -Wpedantic
)