# C. Brr Brrr Patapim

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

Brr Brrr Patapim is trying to learn of Tiramisù's secret passcode, which is a permutation-  of $2\cdot n$ elements. To help Patapim guess, Tiramisù gave him an $n\times n$ grid $G$, in which $G_{i,j}$ (or the element in the $i$-th row and $j$-th column of the grid) contains $p_{i+j}$, or the $(i+j)$-th element in the permutation.

Given this grid, please help Patapim crack the forgotten code. It is guaranteed that the permutation exists, and it can be shown that the permutation can be determined uniquely.

## Input

- The first line contains an integer $t$ — the number of test cases ($1 \leq t \leq 200$).
- The first line of each test case contains an integer $n$ ($1 \leq n \leq 800$).
- Each of the following $n$ lines contains $n$ integers, giving the grid $G$. The first of these lines contains $G_{1,1}, G_{1,2},\ldots,G_{1,n}$; the second of these lines contains $G_{2,1}, G_{2,2},\ldots,G_{2,n}$, and so on. ($1 \leq G_{i,j} \leq 2\cdot n$).
- It is guaranteed that the grid encodes a valid permutation, and the sum of $n$ over all test cases does not exceed $800$.

## Output

- For each test case, please output $2n$ numbers on a new line: $p_1,p_2,\ldots,p_{2n}$.

## Solution

password 의 $i$번째 요소를 $p_{i}$ 라 하면, $G_{i - k,\;i + k}$ = $p_i$ 이다.  
즉, $Grid$ 의 행 과 열 index 의 합이 password 에서의 인덱스 이다.  
문제에서의 조건에 따라 1-based-index 로 접근시, 어떠한 행과 열의 인덱스를 합해도 $1$이 나올수가 없기에,  
마지막에 등장하지 않은 단 하나의 요소가 $p_1$ 이다.

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

constexpr int N_MAX = 800;

void solve(void)
{
    int N;
    cin >> N;

    vector<int> permutation(2 * N + 1, -1);
    vector<bool> checked(2 * N + 1, false);
    int p
    for (int r = 1; r <= N; ++r)
        for (int c = 1; c <= N; ++c)
        {
            cin >> p;
            permutation[r + c] = p;
            checked[p] = true;
        }

    for (int i = 1; i <= 2 * N; ++i)
        if (!checked[i])
        {
            permutation[1] = i;
            break;
        }
    
    for (int i = 1; i <= 2 * N; ++i)
        cout << permutation[i] << ' ';
    cout << ENDL;
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
