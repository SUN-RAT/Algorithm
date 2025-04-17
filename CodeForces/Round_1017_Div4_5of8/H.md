# H. La Vaca Saturno Saturnita

- Time limit : 4 seconds
- Memory limit : 256 megabytes

## Problem Statement

Saturnita's mood depends on an array $a$ of length $n$, which only he knows the meaning of, and a function $f(k, a, l, r)$, which only he knows how to compute. Shown below is the pseudocode for his function $f(k, a, l, r)$.

```plaintext
function f(k, a, l, r):
ans := 0
for i from l to r (inclusive):
    while k is divisible by a[i]:
        k := k/a[i]
        ans := ans + k
return ans
```

You are given $q$ queries, each containing integers $k$, $l$, and $r$. For each query, please output $f(k,a,l,r)$.

## Input

- The first line contains an integer $t$ ($1 \leq t \leq 10^4$) — the number of test cases.
- The first line of each test case contains two integers $n$ and $q$ ($1 \leq n \leq 10^5, 1 \leq q \leq 5\cdot 10^4$).
- The following line contains $n$ integers $a_1,a_2,\ldots,a_n$ ($2 \leq a_i \leq 10^5$).
- The following $q$ lines each contain three integers $k$, $l$, and $r$ ($1 \leq k \leq 10^5, 1 \leq l \leq r \leq n$).
- It is guaranteed that the sum of $n$ does not exceed $10^5$ over all test cases, and the sum of $q$ does not exceed $5\cdot 10^4$ over all test cases.

## Output

- For each query, output the answer on a new line.

## Upsolving

$K$ 의 약수이며, 구간 $[l, r]$ 에 속한 $a_i$ 를 `index` 순으로 정렬시, 아래와 같다고 하자.  
$[a_{k0}, \dots , a_{kd}]$  

구하고자 하는 $ans$ 는 아래의 결과의 총합과 같다.  
$$
\begin{align}
( \text{index of } a_{k0} - \text{index of } a_{l}) &* (\text{divide K until Kmod}a_{k0} \neq 0 \text{ and return K}) \\
( \text{index of } a_{k1} - \text{index of } a_{k0}) &* (\text{divide K until Kmod}a_{k1} \neq 0 \text{ and return K}) \\
( \text{index of } a_{k2} - \text{index of } a_{k1}) &* (\text{divide K until Kmod}a_{k2} \neq 0 \text{ and return K}) \\
&\vdots \\
( \text{index of } a_{kd} - \text{index of } a_{kd - 1}) &* (\text{divide K until Kmod}a_{kd} \neq 0 \text{ and return K})\\
( \text{index of } a_{r} - \text{index of } a_{kd} + 1) &* K \\
\end{align}
$$

$K$ 는 $[1, 10^5]$ 이내의 자연수 이므로, 먼저 해당 범위의 자연수에 대해 모든 약수를 담은 2차원 배열을 전처리 하여, 입력으로 $K$ 가 주어질 때마다, 빠르게 $K$ 의 약수들에 접근 하게한다.  

$K$ 의 약수들에 대해서, 구간 $[l, r]$ 이내의 최초의 인덱스를 찾기 위해, $a_i$ 를 `key` 로, index 벡터를 `value` 로 갖는 `map` 을 활용하여, $log$ 시간 내에 유효한 index 를 선별한다.

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

constexpr int K_MAX = 1e5;
constexpr int N_MAX = 1e5;
constexpr int Q_MAX = 5e4;

array<vector<int>, 1 + K_MAX> Divisor;

void preprocess(void)
{
    for (int num = 2; num <= K_MAX; ++num)
        for (int d = 1; d <= sqrt(num); ++d)
            if (num % d == 0)
            {
                if (d > 1) Divisor[num].push_back(d);
                if (d != num / d) Divisor[num].push_back(num / d);
            }
}

void solve(void)
{
    int N, Q;
    cin >> N >> Q;
    
    map<int, vector<int>> A;
    for (int a, i = 0; i < N; ++i)
    {
        cin >> a;
        A[a].push_back(i);
    }
    for (int k, l, r; Q > 0; --Q)
    {
        cin >> k >> l >> r;
        --l, --r;

        vector<pii> vec;
        for (const int div : Divisor[k])
            if (A.find(div) != A.end())
            {
                auto it = lower_bound(A[div].begin(), A[div].end(), l);
                if (it != A[div].end() && *it <= r)
                    vec.emplace_back(*it, div);
            }
        
        sort(vec.begin(), vec.end());
        ll ans = 0;
        for (const auto &pair : vec)
        {
            auto [index, div] = pair;
            ans += 1LL * (index - l) * k;
            while (k % div == 0) k /= div;
            l = index;
        }
        ans += 1LL * (r - l + 1) * k;
        cout << ans << ENDL;
    }
}

int main(void)
{
    FAST_IO;
    #ifdef SUN_RAT_LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    preprocess();

    int TC;
    cin >> TC;

    while (TC-- > 0)
        solve();

    return 0;
}
```
