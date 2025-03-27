# B. Team Training

- Time limit : 2sec
- Memory limit : 256MB

## Problem Statement

For the next team training session, $N$ students will attend, and the skill of the $i_{th}$ student is given by a positive integer $a_i$.

Coach considers a team **strong** if its **strength is at least $x$**.
The strength of a team is calculated as the number of team members multiplied be the minimum skill among the team members.

Output the maximum possible number of strong teams, given that each team must have at least one participant and every participant must belong to exactly one team.

## Input

- First line contains the number of test caess $t$ (1 $\leq$ $t$ $\leq$ $10^4$)
- First line of each test case contains two integers $N$ and $x$
  - $1 \leq N \leq 2*10^5$ , $1 \leq x \leq 10^9$
- Second line of each test case contains $N$ integers $a_i$ ($1 \leq a_i \leq 10^9$)

## Output

For each test case, output the maximum possible number of strong teams.

## Solution

임의의 team의 strength 는 아래와 같다.\
$strength(team) = size(team) * min\;skill(team)$

team의 strength 함수는 인원 수 와 해당 팀 내의 가장 낮은 $a$ 값에 종속되어 있다.
따라서, 가장 많은 strong team을 만들기 위해서, 충분히 $x$ 이상인 인원은 그 자체로 team을 이루고, 그렇지 않은 인원은 $strength(team) \; \geq x$ 를 만족할 때 까지, 새로운 인원을 추가한다.

이때, 새로운 인원을 추가할 때, 잔여 인원 중에서 가장 높은 $a$인 인원을 선택해야, 다음의 $strength(team)$ 이 최대값이 된다.

```cpp
#ifndef ONLINE_JUDGE
#include <iostream>
#include <algorithm>
#include <queue>
#else
#include <bits/stdc++.h>
#endif

#define FAST_IO std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define ENDL '\n'

using namespace std;

void solve(void)
{
    int N, X;
    cin >> N >> X;

    auto is_strong = [X] (const int team_sz, const int min_a)
    { return 1LL * team_sz * min_a >= X; };

    priority_queue<int> heap;
    for(int a, i = 0; i < N; ++i)
    {
        cin >> a;
        heap.push(a);
    }

    int res = 0;
    int team_size = 0;
    while(!heap.empty())
    {
        int cur_min_a = heap.top();
        heap.pop();
        ++team_size;

        if(is_strong(team_size, cur_min_a))
        {
            ++res;
            team_size = 0;
        }
    }

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

    while (TC-- > 0)
        solve();

    return 0;
}
```
