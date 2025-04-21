# Segment Tree

- `Segment Tree` 는 정보를 구간(`segment`)의 단위로 배열에 저장한 자료구조 이다.
- `Tree` 로서 개념적 추상화를 이루고 있으며, **각 `Node` 는 특정 구간의 정보를 집계 (`Aggregation`) 하여 저장** 한다.
- **범위에 대한 Query** 에 대해 매우 효율적이다.
  - $N$ 개의 정보에 대해 $O(\text{log}N)$ 의 시간 복잡도를 갖는다.
- **동적** 으로 데이터가 변할시, 매우 효과적인 자료구조

## Requirement for Correctness

다음은 `Segment Tree` 의 **정당성을 위해 필요한 조건** 이다.

### 1. Complete Coverage 구간 분할의 완전성

- 원본의 전체 구간이 분할 된 여러 구간들로 **완전히 덮여야 한다** .
  - 하나의 구간에서 빠진 요소가 없어야 하며, 모든 데이터가 하나의 하위 구간으로서 속해야 한다.
  - 각 분할된 구간은 **연속적인 데이터 (`Contiguous Data`)** 를 이루어야 한다.
- **같은 부모 구간으로 부터 분할 된 서로 다른 구간 $A$와 $B$는 서로 $\text{Disjoint}$ 해야 한다.**
  - $\text{Disjoint}$ 하지 않는다면, 중복 연산으로 옳바르지 않은 결과가 도출된다.

### 2. Associativity of Combine Operation 결합 연산의 결합 법칙 준수

서로 다른 구간 $A$ 와 $B$ 를 `merge` 하는 연산을 $M(A, B)$ 라 하자.

- 결합 연산 $M$ 에 대해 **결합 법칙 (`Associativity`)** 가 성립 해야 한다.
  - $M(M\text{(A, B),\,C}) =  M(\text{A, \, M(B, C)})$
  - 연산의 **순서를 어떻게 그룹핑해도 결과가 항상 동일** 해야 한다.
    - 여러 구간의 결과를 병합시, **항상 일관된 결과 보장** 하기 위함.

### 3. Identity Element for Combine Operation 결합 연산에서의 항등원 존재

결합 연산 $M$ 에 대한 항등원을 $I$ 라 하자.

- **빈 구간** 이나 **초기 상태** 를 다루기 위한 **항등원이 존재** 해야 한다.
  - `Empty Segment 처리` 와 `Initial State` 의 옳바름 보장
- 항등원의 존재로 **결합 연산이 항상 정의** 될 수 있도로 보장해야 한다.

## Segment 정의 (Example : Segment {sum, min, max})

위의 `Key Conditions` 을 토대로 아래와 같이 `Node` 와 `Merge` 를 정의 한다.  
예시에서는 간단하게 `int` 범위 이내의 데이터에 대한 `구간 합 sum` 과 `구간 최소값 minimum` 그리고 `구간 최대값 maximum` 을 하나의 `Segment` 에 다룬다.

- `sum` : 구간 $A$ 와 구간 $B$ 를 결합 시, $\text{result sum} = A_{sum} + B_{sum}$ 이다.
  - $+$ 연산에 대해서 항등원은 $0$ 이므로, 초기값으로 $0$ 을 배정한다.
- `min_data` : 구간 $A$ 와 구간 $B$ 를 결합 시, $\text{result min} = min(A_{min},B_{min})$ 이다.
  - $min()$ 함수에 대해서 항등원은 $+\infty$ 이다. 주어진 data의 범위가 `int` 자료형 이내의 범위 이므로, 초기값으로 `numeric_limits<int>::max()` 를 배정한다.
- `max_data` : 구간 $A$ 와 구간 $B$ 를 결합 시, $\text{result max} = max(A_{max},B_{max})$ 이다.
  - $max()$ 함수에 대해서 항등원은 $-\infty$ 이다. 주어진 data의 범위가 `int` 자료형 이내의 범위 이므로, 초기값으로 `numeric_limits<int>::min()` 를 배정한다.

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long int;

struct Segment
{
    ll sum = 0;
    int min_data = numeric_limits<int>::max();
    int max_data = numeric_limits<int>::min();
    Segment() = default;
    inline void update_segment(const int data)
    {
        this->sum = data;
        this->max_data = data;
        this->min_data = data;
    }
    inline void merge(const Segment &L, const Segment &R)
    {
        this->sum = L.sum + B.sum;
        this->min_data = min(L.min_data, R.min_data);
        this->max_data = max(L.max_data, R.max_data);
    }
};
```

`SegmentTree` 구현에는 **재귀를 기반으로 한 방식** 과 **반복을 기반으로 한 방식** 두가지 방식이 있다.

- **재귀 기반** : 구현이 간단하나, **stack 호출 에서의 overhead** 가 크고, **Tree 저장을 위한 메모리 사용량이 크다**.
- **반복 기반** : 구현이 복잡하나, **stack 호출 에서의 overhead** 가 작고, **Tree 저장을 위한 메모리 사용량이 재귀 기반 보다 작다**.

## Recursive SegmentTree Implementation

- 현재의 구간을 $\text{[s, e]}$ 라 할때, 왼쪽 구간은 $\text{[s, s + (e - s)/2]}$, 오른쪽 구간은 $\text{[s + (e - s)/2 + 1, e]}$ 로 설정 한다.
  - 하위 구간이 상위 구간의 전체를 `cover`, 서로간 `disjoint` 함을 만족한다.
- 일반적으로 Tree 저장을 위해 rough 하게 $4*N$ 만큼의 공간을 할당 한다.
- **구간 $\text{[l, r]}$ 에 대한 결과**를 반환한다.

```cpp
template<typename SegmentType>
class SegmentTree
{
private:
    vector<SegmentType> m_Tree;
    int m_SZ;

    void update_tree(const int node, const int s, const int e, const int i, const int data)
    {
        if (s == e)
        {
            m_Tree[node].update_segment(data);
        }
        else
        {
            int mid = s + (e - s) / 2;
            if (i <= mid)
                update_tree(2 * node + 1, s, mid, i, data);
            else
                update_tree(2 * node + 2, mid + 1, e, i, data);
            
            m_Tree[node].merge(m_Tree[2 * node + 1], m_Tree[2 * node + 2]);
        }
    }

    const SegmentType range_query(const int node, const int s, const int e, const int l, const int r)
    {
        if (r < s || e < l)
            return SegmentType();
        if (l <= s && e <= r)
            return m_Tree[node];
        
        int mid = s + (e - s) / 2;
        return SegmentType().merge(range_query(2 * node + 1, s, mid, l, r), range_query(2 * node + 2, mid + 1, e, l, r));
    }
public:
    SegmentTree() = default;
    ~SegmentTree() = default;

    explicit SegmentTree(const int sz) : m_SZ(sz), m_Tree(4 * sz) 
    {
        // build
    }

    void update(const int i, const int data)
    {
        update_tree(0, 0, m_SZ - 1, i, data);
    }

    Segment range(const int l, const int r)
    {
        return range_query(0, 0, m_SZ - 1, l, r);
    }
};
```

## Iterative SegmentTree Implementation

구간 $\text{[l, r)}$ 에 대해 접근을 생각해보자.  
재귀 방식에서 구간 $\text{[l, r)}$ 에 포함되는 최대 크기의 `Segment` 들을 선택하여 $O(logN)$ 의 복잡도로 쿼리를 수행했다.  
반복문 기반에서도 마찬가지로 최대 크기의 `Segment` 선택하되, 재귀에서와 반대로 `leaf` 에서부터 해당 되는 `Segment` 를 찾는다.

- 좀더 쉬운 유도를 위해, $N$ 을 $2^{\lceil\log_2 N\rceil}$ 이고, $H = \lceil\log_2 N\rceil$ 라고 하자.
  - N 을 초과한 잔여 `Segment` 들을 항등원으로 생각해도 성립하여, 꼭 $N$ 을 2의 거듭제곱으로 맞추지 않아도 된다.
- `root` 의 인덱스는 $1$ 이다.
- `leaf` 의 인덱스는 $\text{[sz, 2*sz - 1]}$ 이다.
  - data 요소 하나만을 담당 하는 `leaf` 의 개수가 $N$ 이므로, **조상 node 들의 개수는 $N - 1$** 이다.

### Derivation

`leaf` 에서의 레벨을 $H$ , `root` 에서의 레벨을 $0$ 이라 하자.  
$k$ 레벨 에서의 `Segment` 의 구간 길이는 $2^{H - k}$ 이다.  
$k$ 레벨 에서의 $i$ 번째 `Segment` 의 구간 $\text{Seg[k, i]} = [i*2^{H - k}, (i + 1)*2^{H - k})$ 이라 하자.  

- $\text{left boundary }$ `Segment`

$l$ 을 포함한 최대 `Segment` 의 구간 길이를 $2^{x}$ 라 할때, $x$ 가 가능한 최대값 이어야 한다.  
$\text{Seg[k, i]} = [i*2^{x}, (i + 1)*2^{x}) = [l, l + 2^{x})$  
$l = i * 2^{x}$ 이므로 $i = l / 2^x$ 이다.  
$i$ 는 정수 인덱스 이고, $2^x$ 는 가능한 최대값 이므로, $i$ 는 **항상 홀수 이다**.  
$\therefore$ 왼쪽 경계값 $l$ 을 갖는 최대 `Segment` 는 **인덱스가 홀수** 이다.

- $\text{right boundary }$ `Segment`

반대로, 오른 경계값 $r$ 의 경우, 해당되는 최대 길이 `Segment` 는 $\text{Seg[k, j]} = [j*2^{y}, (i + 1)*2^{y})$  
해당 `Segment` 의 구간의 길이가 $2^y$ 라 할 때,  
$\text{Seg[k, j]} = [j*2^{y}, (j + 1)*2^{y}) = [r - 2^y, r)$  
$r = (j + 1) * 2^y$ 이다. 또한 가능한 최대 길이이므로 $(j + 1)$ 은 홀수  
$\therefore$ 왼쪽 경계값 $r$ 을 갖는 최대 `Segment` 는 **인덱스가 짝수** 이다.

- **Move to next level**

위의 과정 이후 잔여 구간의 경계는 아래와 같다.  
$l_{after} = l + 2^x + 1$ 이 값은 $Seg[i]$ 의 동일 레벨, 오른쪽 `Segment` 가 담당하는 구간의 경계에 해당된다.  
$\therefore \text{next left boundary segment index = i + 1}$  
$r_{after} = r - 2^y$ 이 값은 $Seg[j]$ 의 동일 레벨, 왼쪽 `Segment` 가 담당하는 구간의 경계에 해당된다.  
$\therefore \text{next right boundary segment index = j - 1}$  

이때, $i + 1$ 은 짝수, $j - 1$ 은 홀수 이므로, 절대 최대 `Segment` 에 해당되지 않으므로, 해당 위치에서 부모로 상승하여 탐색을 수행한다.

```cpp
template<typename SegmentType>
class SegmentTree
{
private:
    vector<SegmentType> m_Tree;
    int m_SZ;

public:
    SegmentTree() = default;
    ~SegmentTree() = default;

    explicit SegmentTree(const int sz) : m_SZ(sz), m_Tree(2 * sz) {}

    void update(int i, const int data)
    {
        m_Tree[i += m_SZ].update_segment(data);
        for (int p = i >> 1; p > 0; p >>= 1)
            m_Tree[p].merge(m_Tree[p << 1], m_Tree[(p << 1) | 1]);
    }

    Segment range(int l, int r)
    {
        SegmentType res;
        l += m_SZ, r += m_SZ;
        while (l < r)
        {
            if (l & 1) res.merge(res, m_Tree[l++]);
            if (r & 1) res.merge(res, m_Tree[--r]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};
```
