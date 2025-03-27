# E. Interesting Ratio

- Time limit : 2sec
- Memory limit : 256MB

## Problem Statement

Recently, Misha at the IT Campus "NEIMARK" camp learned a new topic — the Euclidean algorithm.

He was surprised when he realized that $a*b$ = $lcm(a,\;b)*gcd(a,\;b)$.
Misha thought that since the product of LCM and GCD exists, it might be interesting to consider their quotient :
$$ F(a, b) \;=\; \frac{lcm(a,\;b)}{gcd(a,\;b)}$$
Now he considers $F(a,\;b)$ to be an interesting ratio if $a < b$ and $F(a,\;b)$ is a prime number.

How many different pairs of $a$ and $b$ are there such that $F(a,\;b)$ is an interesting ratio and $1\leq a < b \leq N$.

## Input

- First line contains the number of test case $t$. ($1\leq t \leq 10^3$)
- A single line of each test case contains a single integer $N$. ($1\leq N \leq 10^7$)

## Output

For each test case, output the number of pairs.

## Solution

임의의 소수 $F$ 에 대해 $ F\;=\; \frac{lcm(a,\;b)}{gcd(a,\;b)}$ 라 하자.
$F$ 는 $a$ 또는 $b$의 소인수 이다.

**$F$ 는 $a$의 소인수 라면...**\
$a = gcd(a,\;b) * F * \alpha$ 이다.\
$lcm(a, b) \geq a$ 이어야 하므로, $\alpha$ = 1 이다.$\quad$ $\therefore a = gcd(a,\;b) * F$\
그러나 $lcm(a,b) = F * gcd(a,b) = a$ 이므로 이는 모순이다.

**$F$ 는 $b$의 소인수 라면...**\
$b = gcd(a,\;b) * F * \beta$ 이다.\
$lcm(a, b) \geq b$ 이어야 하므로, $\beta$ = 1 이다.$\quad$ $\therefore b = gcd(a,\;b) * F$ 이다.\
$lcm(a,b) = F * gcd(a,b)$ 이므로, $a = gcd(a, b)$ 이다.

$$ \therefore b = F*a $$

$b$ 는 $[1, N]$ 이내에 있으므로, $F$는 $[1, \lfloor N/a \rfloor]$ 이내의 소수 이다.\
가능한 $a$의 범위인 $[1, N-1]$를 선형 순회하며, $[1, \lfloor N/a \rfloor]$ 이내의 소수의 개수를 모두 더한 값이 가능한 pair의 개수이다.

```cpp
#ifndef ONLINE_JUDGE
#include <iostream>
#include <algorithm>
#include <vector>
#else
#include <bits/stdc++.h>
#endif

#define FAST_IO std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define ENDL '\n'

using namespace std;
using ll = long long int;

constexpr int N_MAX = 1e7;

vector<int> prime_num;

void build_prime(void)
{
    prime_num.reserve(N_MAX);
    vector<bool> is_prime(N_MAX + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    for(ll i = 2; i <= N_MAX; ++i)
        if (is_prime[i])
        {
            prime_num.push_back(i);
            for(ll j = i * i; j <= N_MAX; j += i)
                is_prime[j] = false;
        }
}

void solve(void)
{
    int N;
    cin >> N;
    
    ll res = 0;
    for(int a = 1; a < N; ++a)
        res += upper_bound(prime_num.begin(), prime_num.end(), N / a) - prime_num.begin();
    
    cout << res << ENDL;
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

    build_prime();

    while (TC-- > 0)
        solve();

    return 0;
}
```
