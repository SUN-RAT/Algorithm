# G. Chimpanzini Bananini

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

Chimpanzini Bananini stands on the brink of a momentous battle—one destined to bring finality.

For an arbitrary array $b$ of length $m$, let's denote the rizziness of the array to be $\sum_{i=1}^mb_i\cdot i=b_1\cdot 1+b_2\cdot 2+b_3\cdot 3+\ldots + b_m\cdot m$.

Chimpanzini Bananini gifts you an empty array. There are three types of operations you can perform on it.

- Perform a cyclic shift on the array. That is, the array $[a_1, a_2, \ldots, a_n]$ becomes $[a_n, a_1, a_2, \ldots, a_{n-1}].$

- Reverse the entire array. That is, the array $[a_1, a_2, \ldots, a_n]$ becomes $[a_n, a_{n-1}, \ldots, a_1].$

- Append an element to the end of the array. The array $[a_1, a_2, \ldots, a_n]$ becomes $[a_1, a_2, \ldots, a_n, k]$ after appending $k$ to the end of the array.

After each operation, you are interested in calculating the rizziness of your array.

Note that all operations are persistent . This means that each operation modifies the array, and subsequent operations should be applied to the current state of the array after the previous operations.

## Input

- The first line contains an integer $t$ ($1 \leq t \leq 10^4$) — the number of test cases.
- The first line of the input contains an integer $q$ ($1 \leq q \leq 2\cdot 10^5$) — the number of operations you perform on your array.
- The following $q$ lines first contain a single integer $s$ ($1 \leq s \leq 3$) — the operation type.
- It is guaranteed that the sum of $q$ will not exceed $2\cdot 10^5$ over all test cases. Additionally, it is guaranteed that the first operation on each test case will be one with $s=3$.

## Output

- For each test case, output $q$ lines, outputting the rizziness of your array after each operation.

## Solution

```cpp
```
