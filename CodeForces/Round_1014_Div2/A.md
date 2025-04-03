# A. Kamilka and the Sheep

- Time limit : 1sec
- Memory limit : 256MB

## Problem Statement

Kamilka has a flock of $N$ sheep, the $i_{th}$ of which has a beauty level of $A_i$. Morning has come, which means they need to be fed. Kamilka can choose a **non-negative integer $D$** and give each sheep $D$ bunches of grass. After that, the beauty level of each sheep increases by $D$.

In the evening, Kamilka must choose **exactly two** sheep and take them to the mountains. If the beauty levels of these two sheep are $x$ and $y$, then Kamilka's **pleasure from the walk is equal to $\text{gcd}(x,\, y)$**.

The task is to **find the maximum possible pleasure that Kamilka can get from the walk.**\
Note that, **All $a_i$ are distinct.**

## Input

- The first line contains one integer $T$, number of test cases. ($1\leq T \leq 500$)
- The first line of each test case contains $N$, the number of sheep. ($1\leq N \leq 100$)
- The second line of each test case contains $N$ **distinct integers** $a_i$, the beauty levels of the sheep. ($1\leq a_i \leq 10^9$)

## Output

- For each test case, output a single integer : the maximum possible pleasure that Kamilka can get from the walk.

## Solution

모든 $a_i$ 를 **beauty level of sheep 의 초기값** 이라고 할 때, 임의의 날 까지 Kamilka 가 준 먹이의 양을 $D$ 라 하자.\
가능한 **maximum possible pleasure** 는 아래와 같다.
$$\text{max}[gcd(a_i + D, a_j + D)]$$

- 먹이를 줄 때, 모든 양에게 동일한 양 만큼 먹이를 준다.
  - 따라서, 서로 다른 $i$ 와 $j$ 간의 beauty 값 차이는 $abs(a_i - a_j)$ 이다.

문제의 최적해 $a_i = x$, $a_j = y$ 라 하자.\
$gcd(a_i + D, a_j + D)$ 의 상한은 $a_i + D$ 이다. ($a_i < a_j$ 일 때)\
이 경우, $a_j + D$ 는 항상 $a_i + D$ 의 배수 이므로, 아래를 만족한다.

- $a_j - a_i$ = $k*(a_i + D)$ 단, $k$ 는 자연수
  - $\frac{a_j - a_i}{k}$ = $a_i + D$ = $gcd(a_i + D, a_j + D)$ 이므로, 최대값인 경우 $k = 1$ 이다.
  - 따라서, $max(gcd(a_i + D, a_j + D)) \leq a_j - a_i$
    - 위의 $a_j - a_i$ 가 가장 큰 경우는 $a_{max} - a_{min}$ 이다.

```cpp
#include <bits/stdc++.h>

// clang-format off
#define FAST_IO std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define ENDL '\n'
// clang-format on

using namespace std;
using ll = long long int;
using ull = unsigned long long int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int POS_INF = numeric_limits<int>::max();
constexpr int NEG_INF = numeric_limits<int>::min();

void solve(void)
{
    int N;
    cin >> N;

    int mx = NEG_INF, mn = POS_INF;
    for (int a, i = 0; i < N; ++i)
    {
        cin >> a;
        mx = max(mx, a);
        mn = min(mn, a);
    }

    cout << mx - mn << ENDL;
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
