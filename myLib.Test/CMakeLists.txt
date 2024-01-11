include(GoogleTest)

enable_testing()

add_executable (randomTests.Test
  "main.cpp"
  "randomTests.Test.cpp"
)

target_link_libraries(randomTests.Test PRIVATE myLib)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(randomTests.Test PRIVATE GTest::gtest GTest::gmock)

gtest_discover_tests(randomTests.Test DISCOVERY_TIMEOUT 30)