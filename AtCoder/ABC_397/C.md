# C - Variety Split Easy

- Time Limit : 2 sec
- Memory Limit : 1024MB

## Problem Statement

길이가 N 인 정수로 이루어진 수열 A[1, ... , N] 을 입력 받는다.
수열 A 를 두 개의 연속된 sub-array 로 분할 할 시, (양 쪽 모두 빈 수열이 아닌 조건 하에) sum of counts of distinct integers in two subarrays 의 최대값을 구하라.

## Constraints

- 2 $\leq$ N $\leq$ 3*$10^5$
- 1 $\leq$ $A_i$ $\leq$ N
- All input values are integers

## Solution

왼쪽의 sub array 를 L, 오른쪽의 sub array 를 R 이라 하고, L의 마지막 요소를 $A_i$ 라 하자.

L과 R 은 적어도 한개의 요소는 가지고 있으므로, **0-based-index** 기준으로
i $\in$ [1, N - 2] 이다.

i 를 1 부터 N-2 까지 이동 시키며

- $A_i$ 를 R 에서 삭제
- $A_i$ 를 L 에 추가

위의 두가지 연산을 지원하면서 L과 R의 distinct 요소 수 를 추적하며 optimal 값을 찾을 수 있다.

```cpp
#include <iostream>
#include <array>
#include <unordered_map>
#include <algorithm>

using namespace std;

constexpr int N_MAX = 3e5;

array<int, N_MAX> A;
unordered_map<int, int> L; // first : A[i], second : count
unordered_map<int, int> R;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    cin >> N;

    for(int i = 0; i < N; ++i)
    {
        cin >> A[i];
        L[A[i]]++;
    }

    int optimal = 0;
    for(int i = N - 2; i >= 0; --i)
    {   // L : [0, i], R : [i + 1, N - 1]
        R[A[i + 1]]++;
        if(--L[A[i + 1]] == 0)
            L.erase(A[i + 1]);

        optimal = max(optimal, static_cast<int>(L.size() + R.size()));
    }
    cout << optimal;

    return 0;
}```
