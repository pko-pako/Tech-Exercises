cmake_minimum_required(VERSION 3.12)

project(actionsStatic VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(actionsStatic
    actionsSt.cpp
)

target_include_directories(actionsStatic
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_options(actionsStatic PRIVATE -Wall)

# Optionally set the version information for the shared library
set_target_properties(actionsStatic
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
)