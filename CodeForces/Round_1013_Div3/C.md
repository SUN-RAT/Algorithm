# C. Combination Lock

- Time limit : 2sec
- Memory limit : 256MB

## Problem Statement

There are several top-secret rooms where problems for major contests are developed.
To enter one of these rooms, you must unlock a circular lock by selecting the correct code. This code is updated every day.

Today's code is a permutation of the numbers from $1$ to $N$, with the property that in every cyclic shift of it, there is exactly one fixed point.
That is, in every cyclic shift, there exists exactly one element whose value is equal to its position in the permutation.

Output any valid permutation that satisfies this condition.
If a valid permutation not exists, then ouput -1.

- 문제의 Fixed point 는 해당 순열에서 1-based-index 기준 index == value 인 경우, 해당 point를 Fixed point 라 한다.
- 문제의 Cyclic Shift 는 마지막 요소를 시작 요소의 왼쪽으로 옮긴 것을 말한다.

## Input

- First line contains the number of test cases $t$ ($1 \leq t \leq 500$)
- Single line of each test case contains a single integer $N$. ($1 \leq N \leq 2*10^5$)

## Output

For each test case, ouput valid permutation.
If multiple solutions exist, output any one of them.
If no suitable permutations exist, output -1.

## Solution

문제의 조건을 만족하는 길이가 $N$인 순열이 존재한다고 가정하자.
그렇다면, 모든 $P_i$ 에 대해서 $C_i$ 만큼 shift 를 하면 아래를 만족한다.

$P_i$ = $(i + C_i)$ mod $N$ + 1 \
$C_i$ = $(P_i - 1 - i)$ mod $N$

여기서 $c_i$ 는 현재 상태 ($1$ 이 Fixed point 인 상태) 에서 $x$가 Fixed Point 가 되기 위해 수행한 Cyclic Shift 횟수 이다.

모든 $C_i$ 는 [0, $N$ - 1]이내의 서로 다른 정수 이므로, $\sum C_i$ = $N(N - 1) / 2$ 이다.

$\sum C_i$ = $N(N - 1) / 2$ mod $N$ = ($\sum(P_i - 1 - i)$) mod $N$ = 0 이므로,\
$(N - 1) / 2$ 는 정수이어야 한다. 따라서 $N$은 홀수 이다.

```cpp
#ifndef ONLINE_JUDGE
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#else
#include <bits/stdc++.h>
#endif

#define FAST_IO                       \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);
#define ENDL '\n'

using namespace std;

constexpr int N_MAX = 2e5;

void solve(void)
{
    int N; cin >> N;
    vector<int> P(N);
    vector<bool> used(N + 1, false);
    P[0] = 1;
    used[1] = true;
    for(int i = 1; i < N; ++i)
    {
        int cur_num = 2 * i + 1;
        if(cur_num > N)
            cur_num %= N;
        if(used[cur_num])
        {
            cout << -1 << ENDL;
            return;
        }
        else
        {
            P[i] = cur_num;
            used[cur_num] = true;
        }
    }

    for(const int p : P)
        cout << p << ' ';
    cout << ENDL;
}

int main(void)
{
    FAST_IO;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int TC;
    cin >> TC;

    while (TC-- > 0)
        solve();

    return 0;
}
```
