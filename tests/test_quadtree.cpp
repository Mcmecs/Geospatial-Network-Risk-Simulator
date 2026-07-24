#include <gtest/gtest.h>
#include "quadtree.h"
#include <utility>

class QuadtreeTest : public ::testing::Test {
protected:
    BoundingBox root_box = {0.0, 0.0, 50.0, 50.0};

};

TEST_F(QuadtreeTest, VerifySubdivisionWhenCapacityReached) {
    Quadtree qt(root_box, 4);

    // Add the first four stations 
    EXPECT_TRUE(qt.insert(1, -10.0, 10.0)); // NW
    EXPECT_TRUE(qt.insert(2, 10.0, 10.0)); // NE
    EXPECT_TRUE(qt.insert(3, -10.0, -10.0)); // SW
    EXPECT_TRUE(qt.insert(4, 10.0, -10.0)); // SE

    // Add the fifth station within the boundary box
    EXPECT_TRUE(qt.insert(5, 20.0, 20.0));

    // Add sixth station outside the bounadry box
    EXPECT_FALSE(qt.insert(6, 500.0, 500.0));
}