#include <gtest/gtest.h>

// We need to have our own main and not use gtest_main.cc or gmock_main.cc, otherwise our tests will not be discovered
// gtest_main.cc will be used from vcpkg directory
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int runResult = RUN_ALL_TESTS();

  return runResult;
}