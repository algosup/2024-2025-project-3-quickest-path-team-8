#include <gtest/gtest.h>
#include "../include/utils.h"

// Sample test for a function in utils.h
TEST(UtilsTest, AddFunctionWorks) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(-1, 1), 0);
    EXPECT_EQ(add(0, 0), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}