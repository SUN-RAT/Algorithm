# F. Maximize Nor

- Time limit : 4 seconds
- Memory limit : 1024 megabytes

## Problem Statement

The bitwise nor-  of an array of $k$-bit integers $b_1, b_2, \ldots, b_m$ can be computed by calculating the bitwise nor cumulatively from left to right. More formally, $\operatorname{nor}(b_1, b_2, \ldots, b_m) = \operatorname{nor}(\operatorname{nor}(b_1, b_2, \ldots, b_{m - 1}), b_m)$ for $m\ge 2$, and $\operatorname{nor}(b_1) = b_1$.

You are given an array of $k$-bit integers $a_1, a_2, \ldots, a_n$. For each index $i$ ($1\le i\le n$), find the maximum bitwise nor among all subarrays-  of $a$ containing index $i$. In other words, for each index $i$, find the maximum value of $\operatorname{nor}(a_l, a_{l+1}, \ldots, a_r)$ among all $1 \le l \le i \le r \le n$.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
- The first line of each test case contains two integers $n$ and $k$ ($1 \le n \le 10^5$, $1 \le k \le 17$) — the number of elements in the array and the number of bits of the array elements.
- The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($0 \le a_i \le 2^k - 1$) — the elements of array $a$.
- It is guaranteed that the sum of $n$ over all test cases does not exceed $10^5$.

## Output

- For each test case, output $n$ integers, the $i$-th of which is the maximum bitwise nor among all subarrays of $a$ containing index $i$.

## Upsolving

```cpp
```
