/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/counting-bits/
    https://github.com/peniwize/counting-bits.git
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "utils.hpp"

/*
    Given an integer n, return an array ans of length n + 1 such that 
    for each i (0 <= i <= n), ans[i] is the number of 1's in the binary 
    representation of i.

    Constraints:

        * 0 <= n <= 105
*/

/*
    See: https://leetcode.com/problems/counting-bits/solutions/4769871/python-brute-force-dp-full-explanation-t-o-n-s-o-1/
*/
class Solution {
public:
    vector<int> countBits(int n) {

//
//!\todo TODO: >>> Under Construction <<<
//
return {};

    }
};

// {----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------}

namespace doctest {
    const char* testName() noexcept { return doctest::detail::g_cs->currentTest->m_name; }
} // namespace doctest {

TEST_CASE("Case 1")
{
    cerr << doctest::testName() << '\n';
    int n = 2;
    auto const expected = vector<int>{0,1,1};
    auto solution = Solution{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.countBits(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

TEST_CASE("Case 2")
{
    cerr << doctest::testName() << '\n';
    int n = 5;
    auto const expected = vector<int>{0,1,1,2,1,2};
    auto solution = Solution{};
    { // New scope.
        auto const start = std::chrono::steady_clock::now();
        auto const result = solution.countBits(n);
        CHECK(expected == result);
        cerr << "Elapsed time: " << elapsed_time_t{start} << '\n';
    }
    cerr << "\n";
}

/*
    End of "main.cpp"
*/
