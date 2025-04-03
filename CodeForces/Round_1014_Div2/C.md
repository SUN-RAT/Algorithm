# C. Asuna and the Mosquitoes

- Time limit : 2sec
- Memory limit : 256MB

## Problem Statement

For her birthday, each of Asuna's $N$ admirers gifted her a tower. The height of the tower from the $i_{th}$ admirer is equal to $a_i$.

Asuna evaluates the beauty of the received gifts as $max(𝑎_1,𝑎_2,\dots,a_n)$.\
She can perform the following operation an arbitrary number of times (possibly, zero).

Take such $1\leq i \neq j \leq N$ that **$a_i + a_j$ is odd and $0 < a_i$**, then **decrease $a_i$ by 1** and **increase $a_j$ by 1** .\
It is easy to see that the heights of the towers remain non-negative during the operations.
Help Asuna **find the maximum possible beauty of the gifts after any number of operations** !

## Input

- The first line contains one integer $T$, number of test cases. ($1\leq T \leq 10^4$)
- The first line of each test case contains $N$ ($1\leq N \leq 2*10^5$)
- The second line of each test case contains $N$ integers $a_i$ . ($1\leq a_i \leq 10^9$)

## Output

- For each test case, output a single integer : the maximum value of the beauty of the gifts.

## Solution

문제에서 정의한 연산은 두 가지 경우의 수가 있다.

### 1. $a_i$ 는 홀수, $a_j$ 는 짝수

- 결과로 **$a_i$ 는 짝수 (또는 0), $a_j$ 는 홀수** 가 된다.

### 2. $a_i$ 는 짝수, $a_j$ 는 홀수

- 결과로 **$a_i$ 는 홀수, $a_j$ 는 짝수** 가 된다.

**항상 $a_j$ 는 증가하고, 항상 (0 을 짝수에 포함한다고 할 때) 홀수와 짝수의 갯수는 동일하다**.
따라서, **단 하나의 최적해 요소를 제외하고, 모든 짝수 $a_i$ 는 0으로 수렴 가능하며, 모든 홀수 $a_i$ 는 1로 수렴 가능하다.**\
당연히, 최적해 요소 $a_j$ 는 홀수인 경우가 짝수인 경우보다 크기 때문에, 가능한 최적해는 모든 요소의 합에서 최적해를 제외한 홀수의 개수를 뺀 값이다.

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

void solve(void)
{
    int N;
    cin >> N;

    ll total_sum = 0;
    int odd_cnt = 0, even_cnt = 0, mx = 0;
    for (int num, i = 0; i < N; ++i)
    {
        cin >> num;
        mx = max(mx, num);
        total_sum += num;
        if (num & 1)
            odd_cnt++;
        else
            even_cnt++;
    }

    if (odd_cnt == 0 || even_cnt == 0)
        cout << mx << ENDL;
    else
        cout << total_sum - (odd_cnt - 1) << ENDL;
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
