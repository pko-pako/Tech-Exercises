cmake_minimum_required(VERSION 3.12)

project(actionsDynamic VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(actionsDynamic SHARED
    actionsDyn.cpp
)

target_include_directories(actionsDynamic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_options(actionsDynamic PRIVATE -Wall)

# Optionally set the version information for the shared library
set_target_properties(actionsDynamic
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
)