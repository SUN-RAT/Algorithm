# F. Igor and Mountain

- Time limit : 5sec
- Memory limit : 512MB

## Problem Statement

Mountain can be represented as $N \times M$ rectangle, with some cells containing holds.

A route defined as a sequence of distinct holds.
A route is considered valid if the following conditions are satisfied.

- The first hold in the route is located on the very bottom level (row $N$)
- The last hold in the route is located on the very top level (row $1$)
- Each subsequent hold is not lower than the previous one;
- At least one hold is used on each level (i.e., in every row of the rectangle)
- At most two holds are used on each level (since Igor has only two hands)
- Igor can reach from the current hold to the next one if the distance between the centers of the corresponding sections does not exceed Igor's arm span.

Igor's arm span is $D$.
Distance between two different cells is defined as Euclidean distance.

Calculate the number of different valid routes.

## Input

- First line contains the number of test cases $t$. ($1 \leq t \leq 10^3$)
- First line of each test case contains three integers $N, M, D$ ($2\leq N\leq 2000$, $1\leq M, D \leq 2000$)
- Each of the following $N$ lines contains $M$ characters
  - 'X' is hold. '#' is empty.

## Output

For each test case, output the number of different routes modulo 998244353.

## Solution

모든 경로는 $N - 1$ 행의 hold 에서 시작한다. 그리고 $0$ 행에서 끝나므로, $0$ 행의 hold 에 도달한 경로의 수를 모두 더하면 된다.

모든 경로는 같은 행에서 인접한 hold로 또는 위의 행으로 이동 가능 하므로, 두가지의 경로의 합이 해당 위치가 목적지인 경로의 수 이다.
$$ Path(r, c) = Path(r, c)_{from\;bottom} + Path(r, c)_{from\;side} $$

$c_{bottom}$ 은 $(r, c)$ 까지의 거리가 $D$ 이하인 hold 가 있는 $r + 1$행의 열 좌표 이다.\
이때, $c_{bottom}$ 의 범위가 $[lc,\;rc]$ 라 하면,\
구간 $[lc,\;rc]$ 의 $Path(r + 1, c)$ 의 합이 현 위치까지의 경로의 합 이다.
$$ Path(r, c)_{from\;bottom} = \sum Path(r + 1, c_{bottom}) $$

- 이를 선형 순회 할시, 시간 복잡도는 $O(NM^2)$ 이므로 시간 초과

hold 가 아닌 좌표 $(r_{empty}, c_{empty})$에 대해서는 항상 $Path(r_{empty}, c_{empty}) = 0$ 이므로 아래와 같다.
$$ Path(r, c)_{from\;bottom} = \sum^{rc}_{lc} Path(r + 1, c) $$  

임의의 좌표 $(r,c)$ 에서의 $Path(r, c)_{from\;bottom}$ 을 구하고, 있는 좌표 들에 대해 값을 전달하면, $(r,c)$ 에서의 작업은 완료
$$Path(r_{adj}, c_{adj})_{from\;side} += Path(r, c)_{from\;bottom}$$

- 그러나 위와 같이 수행하면, 복잡도가 $O(NM^2)$ 가 된다..

하나의 행에서 $Path(r, c)_{from\;bottom}$ 작업이 모두 완료되면, 현재행을 기점으로 하는 $prefix\;sum$ 배열을 구축한다.
$prefix\;sum$ 배열을 이용하면, $from\;side$ 값을 구할 때 $O(1)$ 복잡도로 계산 가능하므로\
이후, 다음 행에서의 계산을 위해 $from\;bottom + from\;side$ 에 대한 $prefix\;sum$ 을 구축한다. 그렇다면 아래와 같이 $O(1)$ 이내에 $from\;side$ 를 계산 할 수 있다.
$$Path(r, c)_{from\;side} = \sum^{rc}_{lc}Path(r, c_{adj})_{from\;bottom} - Path(r, c)_{from\;side}$$

임의의 행에서 $from\;bottom$ 계산을 위해 $O(M)$, $from\;side$ 계산을 위한 $prefix\;sum$ 구축 $O(M)$, $from\;bottom$ 계산을 위해 $O(M)$, 다음 행에서의 $from\;bottom$ 계산을 위한 $prefix\;sum$ 구축 $O(M)$ 이므로, 총 $O(4M)$의 복잡도 이다.\
따라서, 전체 시간 복잡도는 $O(4NM)$ 이다. 이는 문제의 시간 제한을 만족한다.

```cpp
#ifndef ONLINE_JUDGE
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#else
#include <bits/stdc++.h>
#endif

#define FAST_IO                       \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);
#define ENDL '\n'

using namespace std;
using ll = long long int;

constexpr int LMT = 2000;
constexpr int MOD = 998244353;
constexpr char HOLD = 'X';

struct Node
{
    ll from_bottom = 0;
    ll from_side = 0;
    Node() = default;
};

char board[LMT][LMT];
vector<vector<Node>> DP(LMT, vector<Node>(LMT));
vector<ll> sum;

void solve(void)
{
    int R, C, D;
    cin >> R >> C >> D;

    sum.resize(C, 0);
    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c)
        {
            cin >> board[r][c];
            DP[r][c].from_bottom = 0;
            DP[r][c].from_side = 0;
        }

    for (int c = 0; c < C; ++c)
    {
        if (board[R - 1][c] == HOLD)
            DP[R - 1][c].from_bottom = 1;

        sum[c] = (c > 0 ? sum[c - 1] : 0) + DP[R - 1][c].from_bottom;
    }
    for (int c = 0; c < C; ++c)
        if (board[R - 1][c] == HOLD)
        {
            int rc = min(C - 1, c + D);
            int lc = max(0, c - D);
            DP[R - 1][c].from_side = sum[rc] - sum[lc] + DP[R - 1][lc].from_bottom - DP[R - 1][c].from_bottom;
        }
    for (int c = 0; c < C; ++c)
    {
        sum[c] = (c > 0 ? sum[c - 1] : 0) + DP[R - 1][c].from_bottom + DP[R - 1][c].from_side;
        sum[c] %= MOD;
    }

    for (int r = R - 2; r >= 0; --r)
    {
        for (int c = 0; c < C; ++c)
            if (board[r][c] == HOLD)
            {
                int rc = min(C - 1, (int)floor(c + sqrt(1LL * D * D - 1)));
                int lc = max(0, (int)ceil(c - sqrt(1LL * D * D - 1)));
                DP[r][c].from_bottom = sum[rc] - sum[lc] + (DP[r + 1][lc].from_bottom + DP[r + 1][lc].from_side) + MOD;
                DP[r][c].from_bottom %= MOD;
            }
        for (int c = 0; c < C; ++c)
        {
            sum[c] = (c > 0 ? sum[c - 1] : 0) + DP[r][c].from_bottom;
            sum[c] %= MOD;
        }
        for (int c = 0; c < C; ++c)
            if (board[r][c] == HOLD)
            {
                int rc = min(C - 1, c + D);
                int lc = max(0, c - D);
                DP[r][c].from_side = sum[rc] - sum[lc] + DP[r][lc].from_bottom - DP[r][c].from_bottom + MOD;
                DP[r][c].from_side %= MOD;
            }
        for (int c = 0; c < C; ++c)
        {
            sum[c] = (c > 0 ? sum[c - 1] : 0) + DP[r][c].from_bottom + DP[r][c].from_side;
            sum[c] %= MOD;
        }
    }

    cout << sum[C - 1] << ENDL;
}

int main(void)
{
    FAST_IO;
#ifndef ONLINE_JUDGE
   // freopen("input.txt", "r", stdin);
   // freopen("output.txt", "w", stdout);
#endif

    int TC;
    cin >> TC;

    while (TC-- > 0)
        solve();

    return 0;
}
```
