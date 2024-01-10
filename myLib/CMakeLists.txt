cmake_minimum_required(VERSION 3.12)

project(myLib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(myLib SHARED
    randomTests.cpp
)

target_include_directories(myLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_options(myLib PRIVATE -Wall)

set_target_properties(myLib
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)

# Optionally set the version information for the shared library
set_target_properties(myLib
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
)