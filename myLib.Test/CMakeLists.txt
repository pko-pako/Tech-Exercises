include(GoogleTest)

enable_testing()

add_executable (randomTests.Test
  "main.cpp"
  "randomTests.Test.cpp"
)

target_link_libraries(randomTests.Test PRIVATE myLib myDynamicLib)

if(MSVC)
  add_custom_command(TARGET randomTests.Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:randomTests.Test> $<TARGET_FILE_DIR:randomTests.Test>
    COMMAND_EXPAND_LISTS
  )
endif()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(randomTests.Test PRIVATE GTest::gtest GTest::gmock)

gtest_discover_tests(randomTests.Test DISCOVERY_TIMEOUT 30)