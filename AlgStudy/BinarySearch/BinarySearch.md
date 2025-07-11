# BinarySearch 이분탐색

`BinarySearch` 는 탐색 구간을 **두 개로 분할** 하여 찾고자 하는 대상을 빠르게 찾을 수 있는 기법이다.\
단, `BinarySearch` 를 사용할려면, **두 가지 조건** 이 필요하다.

## Decision Problem 이 Binary 이어야 한다

결정 함수 $f$ 를 주어진 $parameter$ 에 대해 아래와 같이 정의할 수 있을 때, `Binary` 하다고 할 수 있다.\
$f : \{ 0,\,1,\,\dots \, ,\, n-1\} \rightarrow \{0, \, 1\}$\

- 꼭 $\{0, \, 1\}$ 이어야 하는 것이 아니라, **가능한 결과값의 경우의 수가 2가지 이어야 한다.**

### Binary 하지 않다면 ?

$f$ 의 결과가 한 가지 이거나, 두 가지 이상의 경우, 탐색 시 어느 방향으로 탐색 볌위를 줄여야 할 지 결정할 수 없기 때문에, **배제할 구간** 을 정하는 기준이 모호해져 효율적인 탐색이 불가능 하다.

## 결정 함수 $f$ 에 대해 주어진 데이터들이 monotonic (단조) 특성을 가져야 한다

주어진 데이터들이 결정함수 $f$ 에 대해, **어떤 임계값을 기준으로 결과가 한쪽으로만 변해야 한다** .

- ex : 임의의 값 $x$ 이하에서는 $f(x) = 0$ 이고, $x$ 를 초과하면 $f(x) = 1$ 인 경우

### monotonic 하지 않다면 ?

$f(x)$ 가 `monotonic` 하지 않다면, $x$ 의 값이 증가 / 감소 하더라도 $f$ 값이 불규칙하게 나타난다. 이 경우 또한 **배제할 구간** 을 정하기 모호해져 효율적인 탐색이 불가능 하다.

## 구현

현재 구간의 왼쪽 경계를 $l$, 오른쪽 경계를 $r$ 라 할때, 중간 지점 $mid$ 에 대해 $f(mid)$ 에 따라 $l$ 또는 $r$ 을 수정하며 구간의 범위를 좁히는 것이 이분탐색의 기본 아이디어 이다. 단, 항상 종료 한 이후의 $[l, r]$ 내에 찾고자 하는 값이 존재하도록 해야 하므로, 종료 조건식을 아래와 같이 해야 한다.

$l + 1 < r$

단순히 $l < r$ 로 설정할 경우, 마지막에 후보가 하나만 남게되어 후처리가 필요하고, **불변 조건** 을 유지하기가 어렵다.

정렬된 배열 $A$ 에 대해서, $x$ 이상인 가장 작은 값을 찾는다고 하자.\
결정함수 $f$를 $x \leq data$ 라 할 때, $x$ 이상인 모든 요소들은 $f(x) = 1$, $x$ 미만인 요소들은 $f(x) = 0$ 이다.

### Loop In-variant

1. 정답이 항상 구간 $[l, r]$ 내에 존재 한다. ($l < r$)
2. $A[l] < x <= A[r]$ 을 만족해야 한다.

- 초기 조건
  - 1번 조건
    - 배열 $A$의 모든 요소들은 $[l, \, r]$ 이내에 포함되어야 하므로, 초기 $l = -1$, $r = A$의 크기 로 설정한다.
  - 2번 조건
    - $A[-1] = -\infty$, $A[n] = +\infty$ 로 전제 시, 2번 조건을 만족한다.

- 유지 조건
  - 1번 조건
    - `while`문 내에서 항상 $l \leq mid < r$ 이므로, $[l, mid]$ 또는 $[mid, r]$ 내에 항상 정답이 포함되어 있다.
  - 2번 조건
    - $mid$ 를 $l$ 에 대입 한 경우 $(A[mid] < x)$ :
      - $x \leq A[r]$ 임을 알 고 있다. 따라서 $A[mid] = A[l] < x \leq A[r]$ 이므로 만족한다.
    - $mid$ 를 $r$ 에 대입 한 경우 $(x \leq A[mid])$ :
      - $A[l] < x$ 임을 알 고 있다. 따라서 $A[l] < x \leq A[mid] = A[r]$ 이므로 만족한다.

이분 탐색이 종료되면, $l$ 과 $r$ 은 항상 결정문제의 답이 바뀌는 경계에 위치하기 때문에, 요구하는 결정문제의 $f$ 값에 따라 $l$ 또는 $r$ 을 반환 하면 된다.\
예시에서는 $x$ 이상인 가장 작은 값을 찾기 때문에 $f = 1$ 인 $r$ 을 반환하면 된다.

```cpp
#include <vector>

using namespace std;

int binary_search(const vector<int> &vec, const int x)
{
    int n = vec.size();
    int l = -1, r = n;
    
    while(l + 1 < r)
    {
        int mid = l + (r - l) / 2;
        if (vec[mid] < x)
            l = mid;
        else
            r = mid;
    }

    return r;
}
```
