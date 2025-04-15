# H. La Vaca Saturno Saturnita

- Time limit : 4 seconds
- Memory limit : 256 megabytes

## Problem Statement

Saturnita's mood depends on an array $a$ of length $n$, which only he knows the meaning of, and a function $f(k, a, l, r)$, which only he knows how to compute. Shown below is the pseudocode for his function $f(k, a, l, r)$.

```plaintext
function f(k, a, l, r):
ans := 0
for i from l to r (inclusive):
    while k is divisible by a[i]:
        k := k/a[i]
        ans := ans + k
return ans
```

You are given $q$ queries, each containing integers $k$, $l$, and $r$. For each query, please output $f(k,a,l,r)$.

## Input

- The first line contains an integer $t$ ($1 \leq t \leq 10^4$) — the number of test cases.
- The first line of each test case contains two integers $n$ and $q$ ($1 \leq n \leq 10^5, 1 \leq q \leq 5\cdot 10^4$).
- The following line contains $n$ integers $a_1,a_2,\ldots,a_n$ ($2 \leq a_i \leq 10^5$).
- The following $q$ lines each contain three integers $k$, $l$, and $r$ ($1 \leq k \leq 10^5, 1 \leq l \leq r \leq n$).
- It is guaranteed that the sum of $n$ does not exceed $10^5$ over all test cases, and the sum of $q$ does not exceed $5\cdot 10^4$ over all test cases.

## Output

- For each query, output the answer on a new line.

## Solution

```cpp
```
