# B. Lady Bug

- Time limit : 1sec
- Memory limit : 256MB

## Problem Statement

As soon as Dasha Purova crossed the border of France, the villain Markaron kidnapped her and placed her in a prison under his large castle. Fortunately, the wonderful Lady Bug, upon hearing the news about Dasha, immediately ran to save her in Markaron's castle. However, to get there, she needs to crack a complex password.

The password consists of two bit strings $a$ and $b$, each of which has a length of $N$.\
In one operation, Lady Bug can choose any index $2\leq i\leq N$ and perform one of the following actions:

1. swap($a_i$, $b_{i - 1}$)
2. swap($b_i$, $a_{i - 1}$)

Lady Bug can perform any number of operations. The password is considered cracked if she can ensure that the first string consists only of zeros. Help her understand whether or not she will be able to save the unfortunate Dasha.

## Input

- The first line contains one integer $T$, number of test cases. ($1\leq T \leq 10^4$)
- The first line of each test case contains $N$. ($2\leq N \leq 2*10^5$)
- The next two lines contain the bit strings of length $N$, $a$ and $b$. Each characters $0$ and $1$.

## Output

- For each test case, ouput **"YES"** if can crack the password after any number of operations, otherwise ouput **"NO"**.

## Solution

두가지 **swap** 을 살펴보면, 항상 $a$ 의 홀수 인덱스 요소는 $b$ 의 짝수 인덱스 요소와 교환 가능하고, $a$ 의 짝수 인덱스 요소는 항상 $b$ 의 홀수 인덱스 요소와 교환 가능하다.

가장 왼쪽의 $1$ $bit$ 인 $a$ 의 인덱스를 $i$ 라 할 때, $a_i$ 는 항상 $b$ 의 마지막 짝수 또는 홀수 인덱스로 이동할 수 있다. 반대로, $b$ 의 경우에도 $a$의 임의의 짝수 또는 홀수 인덱스로 이동 가능하다.

따라서, **$a$ 의 홀수/짝수 인덱스에서 값이 $1$ 인 요소의 개수** $\leq$ **$b$ 의 짝수/홀수 인덱스에서 값이 $0$ 인 요소의 개수** 를 만족하면, 해당 암호는 crackable 하다.

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
    string a, b;
    cin >> a >> b;

    int odd_a_on = 0, even_a_on = 0;
    int odd_b_off = 0, even_b_off = 0;
    for (int i = 0; i < N; ++i)
    {
        if (i & 1)
        {
            if (a[i] == '1')
                ++odd_a_on;
            if (b[i] == '0')
                ++odd_b_off;
        }
        else
        {
            if (a[i] == '1')
                ++even_a_on;
            if (b[i] == '0')
                ++even_b_off;
        }
    }

    cout << ((even_a_on <= odd_b_off && odd_a_on <= even_b_off) ? "YES" : "NO") << ENDL;
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
