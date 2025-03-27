# A. Olympiad Date

- Time limit / test : 1 sec
- Memory limit / test : 256MB

## Problem Statement

The final of the first Olympiad by IT Campus "NEIMARK" is scheduled for March 1, 2025. A nameless intern was tasked with forming the date of the Olympiad using digits — 01.03.2025.

To accomplish this, the intern took a large bag of digits and began drawing them one by one. In total, he drew $N$ digits.

- digit $a_i$ was drawn in the $i_{th}$ turn.

You suspect that the intern did extra work.
Determine at which step the intern could have first assembled the digits to form the date of the Olympiad (the separating dots can be ignored), or report that it is impossible to form this date from the drawn digits.

- Note that leading zeros must be displayed.

## Input

- First line contains the number of test cases $t$ ( 1 $\leq$ t $\leq $ $10^4$ ).
- The first line of each test case contains a single integer $N$ ( 1 $\leq$ $N$ $\leq$ 20).
- The second line of each test case contains $N$ integers $a_i$ (0 $\leq$ $a_i$ $\leq$ 9)
  - the numbers that the intern pulled out in chronological order.

## Output

For each test case, output the minimum number of digits that the intern could pull out.\
If all the digits cannot be used to make a date, ouput the number 0.

## Solution

$N$ 개의 정수를 입력 받고, 입력 순서대로 순회하며 $a_i$ 정수 까지의 범위에서 $01032025$ 를 형성 가능 한지 검사한다.

```cpp
#ifndef ONLINE_JUDGE
#include <iostream>
#include <array>
#include <algorithm>
#else
#include <bits/stdc++.h>
#endif

#define FAST_IO std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define ENDL '\n'

using namespace std;

constexpr int N_MAX = 20;

array<int, N_MAX> seq;

bool check(const array<int, 10> &cnt)
{
    return cnt[0] >= 3 && cnt[1] >= 1 && cnt[2] >= 2 && cnt[3] >= 1 && cnt[5] >= 1;
}

void solve(void)
{
    array<int, 10> cnt = {};
    
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i)
        cin >> seq[i];
    
    for(int i = 0; i < N; ++i)
    {
        cnt[seq[i]]++;
        if (check(cnt))
        {
            cout << (i + 1) << ENDL;
            return;
        }
    }

    cout << 0 << ENDL;
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

    while (TC-- > 0)
        solve();

    return 0;
}
```
