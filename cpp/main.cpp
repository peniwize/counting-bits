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
    Dynamic programming solution.
    
    See the following for other solutions:
        * https://leetcode.com/problems/counting-bits/solutions/4769871/python-brute-force-dp-full-explanation-t-o-n-s-o-1/
        * https://github.com/peniwize/counting-bits.git

    2**m where m: 4 3 2 1 0  (Each column represents a power of 2.)
                  ---------
          n = 0   0 0 0 0 0  <-- 2**0 (m = 0; cols 1.. are all zero)
              1   0 0 0 0 1
                  ---------
              2   0 0 0 1 0  <-- 2**1 (m = 1; cols 2.. are all zero)
              3   0 0 0 1 1
                  ---------
              4   0 0 1 0 0  <-- 2**2 (m = 2; cols 3.. are all zero)
              5   0 0 1 0 1
              6   0 0 1 1 0
              7   0 0 1 1 1
                  ---------
              8   0 1 0 0 0  <-- 2**3 (m = 3; cols 4.. are all zero)
              9   0 1 0 0 1
             10   0 1 0 1 0
             11   0 1 0 1 1
             12   0 1 1 0 0
             13   0 1 1 0 1
             14   0 1 1 1 0
             15   0 1 1 1 1
                  ---------
             16   1 0 0 0 0  <-- 2**4 (m = 4; cols 5.. are all zero)
             17   1 0 0 0 1
             18   1 0 0 1 0
             19   1 0 0 1 1
                  ...

    First notice that the bit count for n=0 is zero and n=1 is one.  These 
    are the base cases so the result could be initialized with these values.

    Next notice that each power of two ADDS one bit.  This is evident because
    each column (m) will contain all 1's in each region that contains all 
    values >= that power of two and < the next power of two.  For example, 
    column m=0 is 1 for all n=[1, 1]; column m=1 is 1 for all n=[2, 3]; 
    column m=2 is 1 for all n=[4, 7]; colum m=3 is 1 for all n=[8, 15]; 
    and column m=4 is 1 for all n=[16, 31].

    Notice that whenever n is an even value, i.e. the least significant bit
    of n is 0, the number of 1 bits is equal to the previously calculated 
    value for the same relative index/offset in the previous power of two 
    range (m).  For example, the counts for {n=2, n=1} are the same as are
    the counts for {n=4, n=2}, {n=6, n=3}, {n=8, n=4}, {n=10, n=5}, 
    {n=12, n=6}...  The same relative index in the previous power of TWO range
    can be reached by simply dividing n in HALF, which is equivalent to 
    shifting n one bit to the right.

    Also notice that whenever n is an odd value, i.e. the least significant
    bit of n is 1, the number of 1 bits in it is equal to the number of 1 bits
    in the previous n plus one, which makes sense because the value following 
    it has one more bit added.

    T = O(n)

    S = O(1)  [excluding the result itself]
*/
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> result{ 0 };
        result.reserve(++n);
        for (int i = 1; n > i; ++i) {
            result.emplace_back(i & 1 ? result[i - 1] + 1 : result[i >> 1]);
        }
        return result;
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
