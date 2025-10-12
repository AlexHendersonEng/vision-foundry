#include <gtest/gtest.h>

#include "hello/hello.h"

TEST(TestHello, ReturnsZero) { EXPECT_EQ(hello(), 0); }
