# A. Trippi Troppi

- Time limit : 1 second
- Memory limit : 256 megabytes

## Problem Statement

Trippi Troppi resides in a strange world. The ancient name of each country consists of three strings. The first letter of each string is concatenated to form the country's modern name.

Given the country's ancient name, please output the modern name.

## Input

- The first line contains an integer $t$ – the number of independent test cases ($1 \leq t \leq 100$).
- The following $t$ lines each contain three space-separated strings. Each string has a length of no more than $10$, and contains only lowercase Latin characters.

## Output

- For each test case, output the string formed by concatenating the first letter of each word.

## Solution

문제의 요구 사항에 따라 단순히 입력된 3개의 문자열의 첫 글자를 concat 하여 출력한다.

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
    string first, second, third;
    cin >> first >> second >> third;
    cout << first[0] << second[0] << third[0] << ENDL;
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
