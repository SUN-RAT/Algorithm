# E. Ain and Apple Tree

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

If I was also hit by an apple falling from an apple tree, could I become as good at physics as Newton?

To be better at physics, Ain wants to build an apple tree so that she can get hit by apples on it. Her apple tree has $n$ nodes and is rooted at $1$. She defines the weight of an apple tree as $\sum \limits_{i=1}^n \sum \limits_{j=i+1}^n \text{dep}(\operatorname{lca}(i,j))$.

Here, $\text{dep}(x)$ is defined as the number of edges on the unique shortest path from node $1$ to node $x$. $\operatorname{lca}(i, j)$ is defined as the unique node $x$ with the largest value of $\text{dep}(x)$ and which is present on both the paths $(1, i)$ and $(1, j)$.

From some old books Ain reads, she knows that Newton's apple tree's weight is around $k$, but the exact value of it is lost.

As Ain's friend, you want to build an apple tree with $n$ nodes for her, and the absolute difference between your tree's weight and $k$ should be at most $1$ , i.e. $|\text{weight} - k| \le 1$. Unfortunately, this is not always possible, in this case please report it.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
- The first line of each test case contains two numbers $n,k$ ($2 \le n \le 10^5,0 \le k \le 10^{15}$).
- It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

## Output

- For each test case, first output $\texttt{Yes}$ if a solution exists or $\texttt{No}$ if no solution exists. You may print each character in either case, for example $\texttt{YES}$ and $\texttt{yEs}$ will also be accepted.
- If there's at least one solution, print $n-1$ lines and each line contains two numbers $u,v$ $(1 \le u,v \le n)$ represents the apple tree.

## Upsolving

```cpp
```
