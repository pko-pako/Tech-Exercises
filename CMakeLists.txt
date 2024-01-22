cmake_minimum_required(VERSION 3.5)

# Set the project name
project (hello_headers)

enable_testing()

set(CMAKE_CXX_STANDARD 20)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/main.cpp
)

add_subdirectory(myLib)
add_subdirectory(myDynamicLib)
add_subdirectory(myLib.Test)

# Add an executable with the above sources
add_executable(hello_headers ${SOURCES})

target_include_directories(hello_headers PUBLIC 
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(hello_headers
PUBLIC 
    myLib
    myDynamicLib )

if(MSVC)
  add_custom_command(TARGET hello_headers POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:hello_headers> $<TARGET_FILE_DIR:hello_headers>
    COMMAND_EXPAND_LISTS
  )
endif()
