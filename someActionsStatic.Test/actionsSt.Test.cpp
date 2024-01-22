#include <gtest/gtest.h>
#include "actionsStatic.h"
#include "actionsDynamic.h"

namespace randomTestsTest
{
  TEST(randomTestsTest, Sum) {
    int result = sum(1,5);
    int expected = 6;
    EXPECT_EQ(result, expected);
  }

  TEST(randomTestsTest, Equals) {
    bool result = equals(1,5);
    bool expected = false;
    EXPECT_EQ(result, expected);
  }

  TEST(randomTestsDynamicTest, Multiply) {
    int result = multiply(3,5);
    int expected = 15;
    EXPECT_EQ(result, expected);
  }
}