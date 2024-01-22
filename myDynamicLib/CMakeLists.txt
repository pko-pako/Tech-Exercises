cmake_minimum_required(VERSION 3.12)

project(myDynamicLib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(myDynamicLib SHARED
    otherTests.cpp
)

target_include_directories(myDynamicLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_options(myDynamicLib PRIVATE -Wall)

# Optionally set the version information for the shared library
set_target_properties(myDynamicLib
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
)