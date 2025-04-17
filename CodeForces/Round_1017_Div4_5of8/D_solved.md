# D. Tung Tung Sahur

- Time limit : 2 seconds
- Memory limit : 256 megabytes

## Problem Statement

You have two drums in front of you: a left drum and a right drum. A hit on the left can be recorded as " L ", and a hit on the right as " R ".

The strange forces that rule this world are fickle: sometimes, a blow sounds once, and sometimes it sounds twice. Therefore, a hit on the left drum could have sounded as either " L " or " LL ", and a hit on the right drum could have sounded as either " R " or " RR ".

The sequence of hits made is recorded in the string $p$, and the sounds heard are in the string $s$. Given $p$ and $s$, determine whether it is true that the string $s$ could have been the result of the hits from the string $p$.

For example, if $p=$" LR ", then the result of the hits could be any of the strings " LR ", " LRR ", " LLR ", and " LLRR ", but the strings " LLLR " or " LRL " cannot.

## Input

- The first line contains an integer $t$ ($1 \leq t \leq 10^4$) – the number of independent test cases.
- The first line of each test case contains the string $p$ ($1 \le |p| \le 2 \cdot 10^5$) consisting only of the characters " R " and " L ", where $|p|$ denotes the length of the string $p$.
- The second line of each test case contains the string $s$ ($1 \le |p| \le |s| \le 2 \cdot 10^5$) consisting only of the characters " R " and " L ".
- It is guaranteed that the sum of $|s|$ does not exceed $2\cdot 10^5$ across all test cases.

## Output

- For each set of input data, output " YES " if $s$ can be the heard sound, and " NO " otherwise. You may output in any case.

## Solution

`hit` : 단 하나의 $L$ 또는 $R$ 을 기록
`sound` : 하나 ~ 두개의 연속된 $L$ 또는 $R$ 을 기록

위의 조건에 따라 `hit` 에선 $i_{hit}$ 직전 까지, `sound` 에선 $i_{sound}$ 직전 까지 만족한다고 가정하자.  
현재 $i_{hit}$ 와  $i_{sound}$ 에서도 만족 할려면 아래의 두 조건이 충족되어야 한다.

1. $hit[i_{hit}] = sound[i_{sound}]$ 이어야 한다.
2. $hit[i_{hit}] = sound[i_{sound}] = C$ 라고 할 때,  
각 $i$ 에서 부터 연속으로 동일한 $substring$ 의 최대 길이가 $len(sub-hit) \leq 2 * len(sub-sound)$ 이어야 한다.

`hit` 과 `sound` 의 시작 인덱스로 부터 위의 조건을 만족하면서, 다음으로 인접한 최대길이 $substring$ 을 검사하면, 유효한지 아닌지 알 수 있다.

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
    string hit, sound;
    cin >> hit >> sound;

    int l_hit, r_hit, l_sound, r_sound;
    int h = 0, s = 0;
    while(h < hit.length() && s < sound.length())
    {
        char cur_hit = hit[h];
        l_hit = h;
        while(h < hit.length() && cur_hit == hit[h]) ++h;
        r_hit = h - 1;

        char cur_sound = sound[s];
        l_sound = s;
        while(s < sound.length() && cur_sound == sound[s]) ++s;
        r_sound = s - 1;

        if (!(r_hit - l_hit + 1 <= r_sound - l_sound + 1 && r_sound - l_sound + 1 <= 2 * (r_hit - l_hit + 1) && cur_hit == cur_sound))
        {
            cout << "NO" << ENDL;
            return;
        }
    }
    if (h == hit.length() && s == sound.length())
        cout << "YES" << ENDL;
    else
        cout << "NO" << ENDL;
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
