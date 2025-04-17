# E. Boneca Ambalabu

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

Boneca Ambalabu gives you a sequence of $n$ integers $a_1,a_2,\ldots,a_n$.

Output the maximum value of $(a_k\oplus a_1)+(a_k\oplus a_2)+\ldots+(a_k\oplus a_n)$ among all $1 \leq k \leq n$. Note that $\oplus$ denotes the bitwise XOR operation .

## Input

- The first line contains an integer $t$ ($1 \leq t \leq 10^4$) – the number of independent test cases.
- The first line of each test case contains an integer $n$ ($1 \leq n\leq 2\cdot 10^5$) – the length of the array.
- The second line of each test case contains $n$ integers $a_1,a_2,\ldots,a_n$ ($0 \leq a_i < 2^{30}$).
- It is guaranteed that the sum of $n$ over all test cases does not exceed $2\cdot 10^5$.

## Output

- For each test case, output the maximum value on a new line.

## Solution

입력으로 주어지는 모든 $a_i$ 는 $[0, \; 2^{30})$ 이므로, `int` 자료형 으로 모두 표현 가능하다.  
$S_k$ = $(a_k\oplus a_1)+(a_k\oplus a_2)+\ldots+(a_k\oplus a_n)$ 라고 정의하면,  
$S_k$ = $\sum\limits_{i \in [1, n]} (a_k\oplus a_i)$ 이다.  
$a_k$ 의 $j$ 번째 비트를 $bit(a_k, \;j)$ 라고 하면,
$S_k$ = $\sum\limits_{i \in [1, n]} \sum\limits_{j \in [0, 30)}(bit(a_k, \; j)\oplus bit(a_i, \; j))$ 이다.

- $bit(a_k, \;j)$ 가 $1$ 이면,
  - $\sum(bit(a_k, \; j)\oplus bit(a_i, \; j))$ 의 값은 $bit(a_i, \;j)$ 가 $0$ 인 $a_i$ 의 개수에 의해 정해진다.
  - $\sum(bit(a_k, \; j)\oplus bit(a_i, \; j)) = count(bit(a_i, \;j) = 0) * (1 << j)$
- $bit(a_k, \;j)$ 가 $0$ 이면,
  - $\sum(bit(a_k, \; j)\oplus bit(a_i, \; j))$ 의 값은 $bit(a_i, \;j)$ 가 $1$ 인 $a_i$ 의 개수에 의해 정해진다.
  - $\sum(bit(a_k, \; j)\oplus bit(a_i, \; j)) = count(bit(a_i, \;j) = 1) * (1 << j)$

따라서, $S_k$ 는 아래와 같다.

$$S_k = \sum\limits_{j \in [1, 30)} (count(bit(j, \; 1 \; or \;0)) * (1 << j))$$

모든 요소 $a$ 에 대해 $count(bit(j, 1))$ 를 전처리하는 시간은 $O(N * 30)$  
임의의 $a_k$ 에 대한 $S_k$ 의 계산은 $O(30)$  
최대값 $S_k$ 를 구하기 위해 모든 $S_k$ 를 구하므로, 전체 시간 복잡도는 $O(60 * N)$ 이다. 문제의 $N$의 범위에 대해 충분히 제한시간을 만족한다.

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

constexpr int N_MAX = 2e5;
constexpr int BIT_SZ = 30;

array<int, N_MAX> A;
array<int, BIT_SZ> Count;

void solve(void)
{
    fill(Count.begin(), Count.end(), 0);

    int N;
    cin >> N;
    
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
        for (int j = 0; j < BIT_SZ; ++j)
            if (A[i] & (1 << j))
                ++Count[j];
    }

    ll max_S = 0;
    for (int i = 0; i < N; ++i)
    {
        ll S_i = 0;
        for (int j = 0; j < BIT_SZ; ++j)
            if (A[i] & (1 << j))
                S_i += (N - Count[j]) * (1LL << j);
            else 
                S_i += Count[j] * (1LL << j);
        max_S = max(max_S, S_i);
    }

    cout << max_S << ENDL;
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
