# D - Cubes

- Time Limit : 2sec
- Memory Limit : 1024MB

## Problem Statement

You are given a positive integer **N**. Determine whether there exists a pair of positive integers *(x,y)* such that $x^3 - y^3 = N$.

- If such a pair exists, print one such pair *(x,y)*.
- If there is no pair of positive integers *(x,y)* print **-1**.

## Constraints

- 1 $\leq$  N $\leq$ $10^{18}$
- All input values are integers.

## Solution

$x^3 - y^3$ 을 인수분해 하면 아래와 같다.
$(x - y) * (x^2 + xy + y^2) = N$ 이므로, $(x - y) = k$ 라 하면 아래와 같이 전개할 수 있다.\
$(x^2 + xy + y^2) = N / k$\
$x = y + k$\
$((y + k)^2 + (y + k)y + y^2) = N / k$\
$((y + k)^2 + (y + k)y + y^2) = N / k$\
$3y^2 + 3ky + k^2 = N / k$\
$3y^2 + 3ky + k^2 - N / k = 0$ $\;$ $y$에 대한 이차방정식에 근의 공식을 적용하면, $y$ 는 아래와 같다.

$$y = \frac{-3k + \sqrt{12N/k - 3k^2}}{6} $$
$y$ 는 양의 정수 이므로, 중간 기호는 $+$ 이다.

위 공식에서 $-3k + \sqrt{12N/k - 3k^2}$ 이 0 이상 이어야 하므로,
$9k^2 \leq 12N/k - 3k^2$\
$12k^3 \leq 12N$ 이다. (N \> 0 이므로, $k \neq 0$)\
따라서, $0 < k \leq 10^6$ 이다.\
$k$의 범위는 (0, 1'000'000) 으로 설정해도, 충분히 문제의 범위에 대해 닫혀 있음을 알 수 있다.

- N % k == 0 임을 성립한다.
- $N > k^3$ 임을 성립한다.
- $12N/k - 3k^2$ 는 제곱 수 이다.
- $-3k + \sqrt{12N/k - 3k^2}$ 는 6의 배수 이다.

위 조건을 모두 만족하는 y 가 k 의 범위 이내에 존재하는지 선형탐색으로 판별 할 수 있다.

```cpp
#include <iostream>
#include <cmath>

using namespace std;
using ll = unsigned long long int;

constexpr int K_MAX = 1'000'000;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll N;
    cin >> N;

    for(ll k = 1; k <= K_MAX; ++k)
    {
        if (N % k != 0) continue;
        if (N <= k * k * k) continue;

        double d = sqrt(12* N / k - 3 * k * k);
        ll d_int = static_cast<ll>(round(d));
        if (fabs(d - d_int) > 1e-9) continue;

        ll tmp = static_cast<ll>(d) - 3 * k;
        if (tmp % 6 != 0) continue;

        ll y = tmp / 6;
        ll x = y + k;

        if(x * x * x - y * y * y == N)
        {
            cout << x << ' ' << y;
            return 0;
        }
    }

    cout << -1;
    return 0;
}
```

**12 * N 때문에 unsigned long long 자료형을 사용해야 한다...**
