# B. Apples in Boxes

- Time limit : 1 second
- Memory limit : 256 megabytes

## Problem Statement

Tom and Jerry found some apples in the basement. They decided to play a game to get some apples.

There are $n$ boxes, and the $i$-th box has $a_i$ apples inside. Tom and Jerry take turns picking up apples. Tom goes first. On their turn, they have to do the following:

- Choose a box $i$ ($1 \le i \le n$) with a positive number of apples, i.e. $a_i > 0$, and pick $1$ apple from this box. Note that this reduces $a_i$ by $1$.

- If no valid box exists, the current player loses.

- If after the move , $\max(a_1, a_2, \ldots, a_n) - \min(a_1, a_2, \ldots, a_n) > k$ holds, then the current player (who made the last move) also loses.

If both players play optimally, predict the winner of the game.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
- The first line of each test case contains two integers $n,k$ ($2 \le n \le 10^5,1\le k \le 10^9$).
- The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le 10^9$).
- It is guaranteed that the sum of $n$ over all test cases does not exceed $10^5$.

## Output

- For each test case, print "Tom" (without quotes) if Tom will win, or "Jerry" (without quotes) otherwise.

## Solution

먼저, 임의의 플레이어의 턴에서 반드시 지는 경우를 생각해보자.  

- 어떠한 요소를 선택해도 무조건 $max - min > K$ 가 된다면, 해당 플레이어는 반드시 패배한다.  
  - 즉, 선택하기 전 $max - min > K + 1$ 이거나, $max - min = K$ 이지만 $max$ 에 해당되는 요소가 2개 이상인 경우 무조건 패배
- 선택할 요소가 하나도 없는 경우

첫 번째 상황은 항상 첫 번째 턴에서만 발생 한다.  
두 번째 턴 이후에 발생 한다면, 이전의 턴의 결과가 이미 $max - min > K$ 이므로, 모순이기 때문 이다.  

두 번째 상황은 전체 사과의 개수가 홀수인 경우 Tom 의 승리, 짝수인 경우 Jerry 의 승리 이다.  

```cpp
void solve(void)
{
    int N, K;
    cin >> N >> K;

    int mx = 0, mn = 1e9 + 1;
    int mx_cnt = 0;
    ll total = 0;
    for (int a, _ = 0; _ < N; ++_)
    {
        cin >> a;

        total += a;
        mn = min(mn, a);
        if (mx < a)
        {
            mx = a;
            mx_cnt = 1;
        }
        else if (mx == a)
            ++mx_cnt;
    }

    if (mx - mn > K + 1 || (mx - mn == K + 1 && mx_cnt > 1))
        cout << "Jerry" << ENDL;
    else
        cout << (total & 1 ? "Tom" : "Jerry") << ENDL;
}
```
