#include <gtest/gtest.h>

#include <emscripten.h>
#include <emscripten/bind.h>

#include <iostream>

TEST(a, b)
{
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    // ASSERT_TRUE(false) << "failed";
}
