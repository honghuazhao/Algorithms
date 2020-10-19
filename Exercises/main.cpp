#include <iostream>
#include "header.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

vector<int> testArray{3, 1, 5, 4, 6, 2, 7};

TEST_CASE( "LeetCode.215", "[Kth Largest Element]" ) {
    auto test = testArray;
    REQUIRE( findKthLargest(test, 1) == 7 );
    REQUIRE( findKthLargest(test, 2) == 6 );
    REQUIRE( findKthLargest(test, 3) == 5 );
    REQUIRE( findKthLargest(test, 4) == 4 );
}

TEST_CASE( "LeetCode.312", "[Burst Balloons]" ) {
    auto test = testArray;
    REQUIRE( maxCoins(test) == 562 );
}