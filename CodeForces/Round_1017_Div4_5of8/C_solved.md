# C. Brr Brrr Patapim

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

Brr Brrr Patapim is trying to learn of Tiramisù's secret passcode, which is a permutation-  of $2\cdot n$ elements. To help Patapim guess, Tiramisù gave him an $n\times n$ grid $G$, in which $G_{i,j}$ (or the element in the $i$-th row and $j$-th column of the grid) contains $p_{i+j}$, or the $(i+j)$-th element in the permutation.

Given this grid, please help Patapim crack the forgotten code. It is guaranteed that the permutation exists, and it can be shown that the permutation can be determined uniquely.

## Input

- The first line contains an integer $t$ — the number of test cases ($1 \leq t \leq 200$).
- The first line of each test case contains an integer $n$ ($1 \leq n \leq 800$).
- Each of the following $n$ lines contains $n$ integers, giving the grid $G$. The first of these lines contains $G_{1,1}, G_{1,2},\ldots,G_{1,n}$; the second of these lines contains $G_{2,1}, G_{2,2},\ldots,G_{2,n}$, and so on. ($1 \leq G_{i,j} \leq 2\cdot n$).
- It is guaranteed that the grid encodes a valid permutation, and the sum of $n$ over all test cases does not exceed $800$.

## Output

- For each test case, please output $2n$ numbers on a new line: $p_1,p_2,\ldots,p_{2n}$.

## Solution

```cpp
```
