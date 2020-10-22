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

int topToBottom(string& s) {
    vector<vector<int>> memo(s.length(), vector<int>(s.length(), 0));
    return helper(s, 0, s.length()-1, memo);
}

int bottomToTop(string& s) {
    vector<vector<int>> dp(s.length()+1, vector<int>(s.length(), 0));
    for(int i = 0; i < s.length(); i++)
        dp[1][i] = 1;
    for(int len = 2; len <= s.length(); len++){
        for(int i = 0; i < s.length()-len+1; i++) {
            dp[len][i] = s[i] == s[i+len-1]? dp[len-2][i+1]+2 :
                    max(dp[len-1][i], dp[len-1][i+1]);
        }
    }
    return dp[s.length()][0];
}

int longestPalindromeSubseq(string s) {
    if(s == "") return 0;
    return bottomToTop(s);
}


TEST_CASE( "LeetCode.516", "[Longest Palindromic Subsequence]" ) {
    REQUIRE( longestPalindromeSubseq("bbbab") == 4 );
    REQUIRE( longestPalindromeSubseq("bb") == 2 );
    REQUIRE( longestPalindromeSubseq("") == 0 );
    REQUIRE( longestPalindromeSubseq("aaaaaaaaaa") == 10 );
}