# D. Apple Tree Traversing

- Time limit : 5 seconds
- Memory limit : 512 megabytes

## Problem Statement

There is an apple tree with $n$ nodes, initially with one apple at each node. You have a paper with you, initially with nothing written on it.

You are traversing on the apple tree, by doing the following action as long as there is at least one apple left:

- Choose an apple path $(u,v)$. A path $(u,v)$ is called an apple path if and only if for every node on the path $(u,v)$, there's an apple on it.

- Let $d$ be the number of apples on the path, write down three numbers $(d,u,v)$, in this order, on the paper.

- Then remove all the apples on the path $(u,v)$.

Here, the path $(u, v)$ refers to the sequence of vertices on the unique shortest walk from $u$ to $v$.

Let the number sequence on the paper be $a$. Your task is to find the lexicographically largest possible sequence $a$.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
- The first line of each test case contains a number $n$ ($1 \le n \le 1.5 \cdot 10^5$).
- The following $n-1$ lines of each test case contain two numbers $u,v$ ($1 \le u,v \le n$). It's guaranteed that the input forms a tree.
- It is guaranteed that the sum of $n$ over all test cases does not exceed $1.5 \cdot 10^5$.

## Output

- For each test case, output the lexicographically largest sequence possible $a_1, a_2, \ldots, a_{|a|}$. It can be shown that $|a| \le 3 \cdot n$.

## Solution

```cpp
```
