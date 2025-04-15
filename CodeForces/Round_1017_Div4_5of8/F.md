# F. Trulimero Trulicina

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

Trulicina gives you integers $n$, $m$, and $k$. It is guaranteed that $k\geq 2$ and $n\cdot m\equiv 0 \pmod{k}$.

Output a $n$ by $m$ grid of integers such that each of the following criteria hold:

- Each integer in the grid is between $1$ and $k$, inclusive.

- Each integer from $1$ to $k$ appears an equal number of times.

- No two cells that share an edge have the same integer.

It can be shown that such a grid always exists. If there are multiple solutions, output any.

## Input

- The first line contains an integer $t$ ($1 \leq t \leq 10^4$) — the number of test cases.
- The first line of each test case contains three integers $n$, $m$, and $k$ ($2 \leq n\cdot m\leq 2\cdot 10^5, 2\leq k\leq n\cdot m, n\cdot m\equiv 0 \pmod{k})$.
- It is guaranteed that the sum of $n\cdot m$ over all test cases does not exceed $2\cdot 10^5$.

## Output

- For each test case, output $n$ lines, each containing $m$ integers that satisfy the criteria. If there are multiple solutions, output any.

## Solution

```cpp
```
