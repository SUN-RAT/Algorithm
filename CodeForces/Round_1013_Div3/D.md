# D. Place of the Olympiad

- Time limit : 1sec
- Memory limit : 256MB

## Problem Statement

For the final of the first Olympiad by IT Campus, a rectangular venue was prepared.\
The venue is divided into $N$ rows, each containing $M$ spots for participant's desks.\
A total of $K$ participants have registered for the final, and each participant will sit at an individual desk.\
Committee must choose the locations for the desks in the venue.\
If several desks occupy consecutive spots in the same row, we call such a group of desks a **bench**, and the number of desks in the group is the bench's length.\

Committee wants to choose the locations so that the length of the longest bench is as small as possible.
Given the integers $N$, $M$, and $K$, determine the minimum possible length of the longerst bench.

## Input

- First line contains the number of test cases $t$. ($1 \leq t \leq 10^4$)
- A single line of each test case contains three positive integers $N$, $M$, $K$.
  - ($1 \leq N, M, K \leq 10^9$)

## Output

For each test case, ouput a single number - the minimum possible length of the longest bench.

## Solution

비둘기집 원리로 $K$ 명에 대해 배치 시, 가장 많은 배치행의 좌석 수는 $\lceil K / N\rceil$ 이다.\

- $req$ = $\lceil K / N\rceil$

임의의 행에서 가장 긴 bench의 길이가 $l$ 일 때, 해당 행에서 앉힐 수 있는 인원의 수는 아래와 같다.

- $bench \; count$ = $\lfloor req/l \rfloor$
  - $req\;\text{mod}\;l$ = 0 이면, $cap$ = $l * bench\;count + bench\;count\; - 1$
  - $req\;\text{mod}\;l$ > 0 이면, $cap$ = $l * bench\;count + bench\;count\; + \; req\;\text{mod}\;l$

$cap \leq M$ 이어야 한다.\
가능한 $l$ 의 범위는 $[1, \; M]$ 이고, 위의 식에 대해 monotonic 하므로, 이분 탐색으로 최소의 bench길이를 알 수 있다.

```cpp
#ifndef ONLINE_JUDGE
#include <iostream>
#include <algorithm>
#else
#include <bits/stdc++.h>
#endif

#define FAST_IO std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define ENDL '\n'

using namespace std;

inline bool check(const int req, const int bench_len, const int M)
{
    int cap;
    if (req % bench_len == 0)
        cap = 1LL * bench_len * (req / bench_len) + req / bench_len - 1;
    else
        cap = 1LL * bench_len * (req / bench_len) + (req / bench_len) + req % bench_len;

    return cap <= M;
}

void solve(void)
{
    int N, M, K;
    cin >> N >> M >> K;

    int req = K / N + (K % N == 0 ? 0 : 1);
    int l = 0, r = M + 1;
    while(l + 1 < r)
    {
        int mid = l + (r - l) / 2;
        if(check(req, mid, M))
            r = mid;
        else
            l = mid;
    }
    cout << r << ENDL;
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
