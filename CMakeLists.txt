cmake_minimum_required(VERSION 3.5)

# Set the project name
project (tech-exercises)

enable_testing()

set(CMAKE_CXX_STANDARD 20)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/main.cpp
)

add_subdirectory(someActionsStatic)
add_subdirectory(someActionsDynamic)
add_subdirectory(someActionsStatic.Test)

# Add an executable with the above sources
add_executable(tech-exercises ${SOURCES})

target_include_directories(tech-exercises PUBLIC 
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(tech-exercises
PUBLIC 
    actionsStatic
    actionsDynamic )

if(MSVC)
  add_custom_command(TARGET tech-exercises POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:tech-exercises> $<TARGET_FILE_DIR:tech-exercises>
    COMMAND_EXPAND_LISTS
  )
endif()
