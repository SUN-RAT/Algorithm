# B - Ticket Gate Log

- Time Limit : 2sec
- Memory Limit : 1024MB

## Problem Statement

Takahashi aggregated usage records from ticket gates. However, he accidentally erased some records of entering and exiting stations. He is trying to restore the erased records.

- You are given a string S consisting of **i** and **o**.
- We want to insert zero or more characters at arbitrary positions in S so that the resulting string satisfies the following conditions.
  - Its length is **even**.
  - **every odd-numbered** character is **i** while **every even-numbered** character is **o**.

**Find the minimum number of characters that need to be inserted.**

## Constraints

- S is a string of length [1, 100].

## Solution

입력으로 주어지는 S 는 기록의 일부가 사라진 문자열이다.
주어진 입력을 받으며, 복원하는 문자열의 index 에 맞는 조건이 아닌 경우 조건에 맞는 문자를 먼저 추가하고 입력의 문자를 읽는다.
하지만, 입력이 끝난 직후 복원한 문자열의 길이 조건에 따라 마지막 문자 **o** 를 추가해야 한다.

- 문제의 조건에선 **1-based-indexing** 임을 주의 해야 한다.

```cpp
#include <iostream>

using namespace std;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char c;
    int answer = 0, i = 0;

    while(cin >> c)
    {
        if(i % 2 == 0)
        {
            if (c == 'o')
            {
                answer++;
                ++i;
            }
        }
        else
        {
            if (c == 'i')
            {
                answer++;
                ++i;
            }
        }
        ++i;
    }

    if (i % 2 != 0)
        answer++;

    cout << answer;

    return 0;
}```
