//
// Created by zhaohonghua on 10/22/20.
//
#include "header.h"
#include "catch.hpp"

int helper(string& s, int start, int end, vector<vector<int>>& memo) {
    if(start == end)
        return 1;
    if(start > end)
        return 0;

    if(memo[start][end] > 0) return memo[start][end];

    int ans = s[start] == s[end]? helper(s, start+1, end-1, memo)+2
                                : max(helper(s, start, end-1, memo),
                                      helper(s, start+1, end, memo));
    memo[start][end] = ans;
    return ans;
}

int intuitive(string& s) {
    vector<vector<int>> memo(s.length(), vector<int>(s.length(), 0));
    return helper(s, 0, s.length()-1, memo);
}

int longestPalindromeSubseq(string s) {
    return intuitive(s);
}


TEST_CASE( "LeetCode.516", "[Longest Palindromic Subsequence]" ) {
    REQUIRE( longestPalindromeSubseq("bbbab") == 4 );
    REQUIRE( longestPalindromeSubseq("bb") == 2 );
    REQUIRE( longestPalindromeSubseq("") == 0 );
    REQUIRE( longestPalindromeSubseq("aaaaaaaaaa") == 10 );
}