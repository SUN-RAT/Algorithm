# A. Common Multiple

- Time limit : 1 second
- Memory limit : 256 megabytes

## Problem Statement

You are given an array of integers $a_1, a_2, \ldots, a_n$. An array $x_1, x_2, \ldots, x_m$ is beautiful if there exists an array $y_1, y_2, \ldots, y_m$ such that the elements of $y$ are distinct (in other words, $y_i\neq y_j$ for all $1 \le i < j \le m$), and the product of $x_i$ and $y_i$ is the same for all $1 \le i \le m$ (in other words, $x_i\cdot y_i = x_j\cdot y_j$ for all $1 \le i < j \le m$).

Your task is to determine the maximum size of a subsequence-  of array $a$ that is beautiful.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 500$). The description of the test cases follows.
- The first line of each test case contains a single integer $n$ ($1 \le n \le 100$) — the length of the array $a$.
- The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le n$) — the elements of array $a$.
- Note that there are no constraints on the sum of $n$ over all test cases.

## Output

- For each test case, output the maximum size of a subsequence of array $a$ that is beautiful.

## Solution

문제의 `beautiful` 조건에 대해 살펴보자.  

길이가 $N$ 인 임의의 정수 배열 $A$ 에 대한 `subsequence` 를 $A^{sub}$ 라 하자. 그리고 $A^{sub}$ 의 길이를 $M$ 이라 할 때,  

$A^{sub}$ 가 `beautiful` 하려면,  

```math
A[0] * Y[0] = K \\
A[1] * Y[1] = K \\
A[2] * Y[2] = K \\
\vdots \\
A[M-2] * Y[M-2] = K \\
A[M-1] * Y[M-1] = K \\
```

위 조건을 만족해야 한다.  
동시에 $A[M]$ 과 $Y[M]$ 의 모든 요소는 각 배열 내에서 `unique` 해야 한다.  

```cpp
void solve(void)
{
    set<int> num_set;
    int N;
    cin >> N;

    int a;
    while((N-- > 0) && (cin >> a))
        num_set.insert(a);
    
    cout << num_set.size() << ENDL;    
}
```
