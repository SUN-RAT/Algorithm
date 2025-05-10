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

```cpp
```
