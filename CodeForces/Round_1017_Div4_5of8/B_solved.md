# B. Bobritto Bandito

- Time limit : 1 second
- Memory limit : 256 megabytes

## Problem Statement

In Bobritto Bandito's home town of residence, there are an infinite number of houses on an infinite number line, with houses at $\ldots, -2, -1, 0, 1, 2, \ldots$. On day $0$, he started a plague by giving an infection to the unfortunate residents of house $0$. Each succeeding day, the plague spreads to exactly one healthy household that is next to an infected household. It can be shown that each day the infected houses form a continuous segment.

Let the segment starting at the $l$-th house and ending at the $r$-th house be denoted as $[l, r]$. You know that after $n$ days, the segment $[l, r]$ became infected. Find any such segment $[l', r']$ that could have been infected on the $m$-th day ($m \le n$).

## Input

- The first line contains an integer $t$ ($1 \leq t \leq 100$) – the number of independent test cases.
- The only line of each test case contains four integers $n$, $m$, $l$, and $r$ ($1 \leq m\leq n \leq 2000, -n \leq l \leq 0 \leq r \leq n, r-l=n$).

## Output

- For each test case, output two integers $l'$ and $r'$ on a new line. If there are multiple solutions, output any.

## Solution

문제의 조건에 따라 전염병은 하루에 하나의 집으로, 바로 인접한 집으로 퍼져 나간다.  
$i$ 번째 날의 전염된 segment 가 $[L_i, R_i]$ 라면, $i + 1$ 번째 날의 segment 는 $[L_i - 1, R_i]$ 또는 $[L_i, R_i + 1]$ 이다.  
항상 $L_i \leq 0$ 이고, $0 \leq R_i$ 이므로, 조건에 맞춰 $N - M$ 만큼 양끝에서 하나의 집을 선택하여 제거하면, 문제에서 요구하는 $M_{th} Day$ 에서의 가능한 segment 이다.

```cpp
#include <bits/stdc++.h>

// clang-format off
#define FAST_IO std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define ENDL '\n'
// clang-format on

using namespace std;
using u_int = unsigned int;
using ll = long long int;
using u_ll = unsigned long long int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;


void solve(void)
{
    int n, m, l, r;
    cin >> n >> m >> l >> r;

    int req = n - m;
    while (req-- > 0)
    {
        if (l < 0)
            ++l;
        else if (r > 0)
            --r;
    }
    cout << l << ' ' << r << ENDL;
}

int main(void)
{
    FAST_IO;
#ifdef SUN_RAT_LOCAL
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
