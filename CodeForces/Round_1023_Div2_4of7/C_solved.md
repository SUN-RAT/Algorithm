# C. Maximum Subarray Sum

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

You are given an array $a_1,a_2,\ldots,a_n$ of length $n$ and a positive integer $k$, but some parts of the array $a$ are missing. Your task is to fill the missing part so that the maximum subarray sum -  of $a$ is exactly $k$, or report that no solution exists.

Formally, you are given a binary string $s$ and a partially filled array $a$, where:

- If you remember the value of $a_i$, $s_i = 1$ to indicate that, and you are given the real value of $a_i$.

- If you don't remember the value of $a_i$, $s_i = 0$ to indicate that, and you are given $a_i = 0$.

All the values that you remember satisfy $|a_i| \le 10^6$. However, you may use values up to $10^{18}$ to fill in the values that you do not remember. It can be proven that if a solution exists, a solution also exists satisfying $|a_i| \le 10^{18}$.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
- The first line of each test case contains two numbers $n,k$ ($1 \le n \le 2 \cdot 10^5,1 \le k \le 10^{12}$).
- The second line of each test case contains a binary ($\texttt{01}$) string $s$ of length $n$.
- The third line of each test case contains $n$ numbers $a_1,a_2,\ldots,a_n$ ($|a_i| \le 10^6$). If $s_i = \texttt{0}$, then it's guaranteed that $a_i = 0$.
- It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

## Output

- For each test case, first output $\texttt{Yes}$ if a solution exists or $\texttt{No}$ if no solution exists. You may print each character in either case, for example $\texttt{YES}$ and $\texttt{yEs}$ will also be accepted.
- If there's at least one solution, print $n$ numbers $a_1,a_2,\ldots,a_n$ on the second line. $|a_i| \le 10^{18}$ must hold.

## Solution

```cpp
```
