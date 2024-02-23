# Start of "solution.py".

from collections import deque
import copy
import inspect
import time
from typing import List
from typing import Optional
from typing import Set

"""
    Given an integer n, return an array ans of length n + 1 such that 
    for each i (0 <= i <= n), ans[i] is the number of 1's in the binary 
    representation of i.

    Constraints:

        * 0 <= n <= 105
"""

"""
    Loop through each each n and convert n into a bit count using the 
    compiler/language intrinsic, which is assumed to be O(1).

    T = O(n)

    S = O(1)
"""
class Solution1_BruteForce:
    def countBits(self, n: int) -> List[int]:
        result = []
        for i in range(n + 1):
            result.append(i.bit_count())
        return result

"""
    Use a table of n -> bit count values to convert n into a bit count.
    The table size may be less than n.  When this is the case, break n
    down into table sized values and add up the values from the table.

    T = O(n)

    S = O(1)  [excluding the table]
"""
class Solution2_Table:
    __TO_BIT_COUNT = [
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
    ]
    def countBits(self, n: int) -> List[int]:
        result = []
        for i in range(n + 1):
            if 256 > i:
                result.append(self.__TO_BIT_COUNT[i])
            elif 65536 > i:
                result.append(
                    self.__TO_BIT_COUNT[i & 0xff]
                    + self.__TO_BIT_COUNT[(i >> 8) & 0xff]
                )
            else:
                result.append(
                    self.__TO_BIT_COUNT[i & 0xff]
                    + self.__TO_BIT_COUNT[(i >> 8) & 0xff]
                    + 1 if i & 0x10000 else 0
                )
        return result

"""
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
"""
class Solution3_DP:
    def countBits(self, n: int) -> List[int]:
        result = [0]
        for i in range(1, n + 1):
            if i & 1:
                result.append(result[i - 1] + 1)
            else:
                result.append(result[i >> 1])
        return result

def test1(solution):
    n = 2
    expected = [0,1,1]
    startTime = time.time()
    result = solution.countBits(n)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

def test2(solution):
    n = 5
    expected = [0,1,1,2,1,2]
    startTime = time.time()
    result = solution.countBits(n)
    endTime = time.time()
    print("{}:{}({:.6f} sec) result = {}".format(inspect.currentframe().f_code.co_name, type(solution), endTime - startTime, result))
    assert(expected == result)

if "__main__" == __name__:
    test1(Solution1_BruteForce())
    test1(Solution2_Table())
    test1(Solution3_DP())

    test2(Solution1_BruteForce())
    test2(Solution2_Table())
    test2(Solution3_DP())

# End of "solution.py".
