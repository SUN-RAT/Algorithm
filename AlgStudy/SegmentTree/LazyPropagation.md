# SegmentTree - Lazy Propagation (지연전파)

- `range query` 와 `range update` 모두 $O(logN)$ 이내에 수행가능한 기법
- 기본적으로 해당 `Segment` 가 질의에 필요한 순간까지 update 를 최소한으로 하며 누적시킨다.

구간 $\text{[l, r)}$ 에 대해 `range update` 를 수행한다고 하자.
임의의 leaf node 까지 $O(logN)$ 으로 도달 가능하다 해도 `range update` 의 경우 하나씩 갱신할 시, $O(NlogN)$ 이 걸리게 된다.  

하지만, 구간 $\text{[l, r)}$ 을 완전히 덮는 최대 크기의 `Segment` 들 까지만 갱신을 한다면 어떨까?

왼쪽 경계 $l$ 을 경계로 갖는 최대 크기의 유효한 `Segment` 를 $S_{l0}$, 오른쪽 경계 $r$ 을 경계로 갖는 최대 크기의 유효한 `Segment` 를 $S_{r0}$ 라 하자.  
남은 잔여 구간은 $\text{[l + l0, r - r0)}$ 이다.  
위의 잔여 구간이 유효하지 않을때 까지, 즉, $\text{L = R}$ 이 될때 까지 수행하면,  
왼쪽 경계를 경계로 갖는 $S_L$ 의 개수와 $S_R$ 의 개수의 상한값은 $2 * log(r - l)$ 이다.  

따라서, 구간 이내의 최대 크기의 `Segment` 까지만 갱신을 하는 경우 `range update` 를 $O(logN)$ 복잡도 이내로 해결할 수 있다.  

그렇다면, 질의의 대상이 되는 `Segment` 의 갱신에 대해 생각해보자.  
임의의 `Segment` 에서 하위의 자식으로 이동을 할때, **현재 update 여부 (이하 lazy)** 가 있다면, 이동과 동시에 `propagation` 을 수행한다.  

위의 방식이 옳바름을 증명해보자.

- **Invariant**
  - `Segment` 값 일관성
    - 방문한 `Segment` 에는 담당하는 구간에 적용된 **모든 update** 가 반영된 상태이어야 한다.
  - `lazy[node]` 가 유효 하다면, 그 값은 아직 **자식에게 전파되지 않은 update 만** 남아 있어야 한다.  

- Base Case
  - build 직후, 모든 `Segment` 는 update 가 없다. (`Segment` 일관성 충족)
  - 모든 `lazy[node]` 값은 유효하지 않은 값으로 초기화 되어 있다.
- `lazy propagation` 연산
  - 전제 : 호출 전, 불변식 $I_1$ 과 $I_2$ 가 모두 성립
  - $value_i \leftarrow value_i + lazy_i \cdot [l_i, r_i)$
  - 자식이 존재할 시, $lazy_{left} \leftarrow lazy_{left} + lazy_{i}$ , $lazy_{right}$ 도 동일 하게 수행
  - $lazy_i \leftarrow 0$
    - 동작 이후, $i$ 번째 `Segment` 는 모든 update 가 적용되었으며, `lazy` 값은 유효하지 않다. $I_1$ 성립
    - $i$ 번째 `Segment` 의 자식은 구간에 해당되는 모든 적용되지 않은 update 가 자식의 `lazy` 에 포함되어 있다. $I_2$ 성립

## Implementation - Recursive

- 재귀 기반은 `closed interval` 로 구현

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long int;

struct LazyNode
{
    int delta = 0;
    LazyNode() = default;
    inline bool has_update(void) const
    { return delta != 0; }
    inline void combine(const LazyNode &p)
    { this->delta += p.delta; }
    inline void combine(const int data)
    { this->delta += data; }
    inline void reset(void)
    { this->delta = 0; }
};
struct Segment
{
    ll sum = 0;
    int min_data = numeric_limits<int>::max();
    int max_data = numeric_limits<int>::min();
    Segment() = default;
    void update_segment(const int data)
    {
        this->sum = data;
        this->max_data = data;
        this->min_data = data;
    }
    void merge(const Segment &L, const Segment &R)
    {
        this->sum = L.sum + R.sum;
        this->min_data = min(L.min_data, R.min_data);
        this->max_data = max(L.max_data, R.max_data);
    }
    void apply(const LazyNode &lazy, const int range)
    {
        this->sum += 1LL * lazy.delta * range;
        this->min_data += lazy.delta;
        this->max_data += lazy.delta;
    }
    void apply(const int data, const int range)
    {
        this->sum += 1LL * data * range;
        this->min_data += data;
        this->max_data += data;
    }
};

template<typename SegmentType, typename LazyType>
class LazySegmentTree
{
private:
    int m_SZ;
    vector<SegmentType> m_Tree;
    vector<LazyType> m_Lazy;

    void propagation(const int node, const int s, const int e)
    {
        m_Tree[node].apply(m_Lazy[node], e - s + 1);
        if (s < e) // has children
        {
            m_Lazy[2 * node + 1].combine(m_Lazy[node]);
            m_Lazy[2 * node + 2].combine(m_Lazy[node]);
        }
        m_Lazy[node].reset();
    }

    void update_element(const int node, const int s, const int e, const int i, const int data)
    {
        if (m_Lazy[node].has_update())
            propagation(node, s, e);

        if (s == e)
        {
            m_Tree[node].update_segment(data);
        }
        else
        {
            int mid = s + (e - s) / 2;
            if (i <= mid)
                update_element(2 * node + 1, s, mid, i, data);
            else
                update_element(2 * node + 2, mid + 1, e, i, data);
            
            m_Tree[node].merge(m_Tree[2 * node + 1], m_Tree[2 * node + 2]);
        }
    }

    void update_range(const int node, const int s, const int e, const int l, const int r, const int data)
    {
        if (m_Lazy[node].has_update())
            propagation(node, s, e);
        
        if (r < s || e < l)
            return;
        if (l <= s && e <= r)
        {
            m_Tree[node].apply(data, e - s + 1);
            if (s < e)
            {
                m_Lazy[2 * node + 1].combine(data);
                m_Lazy[2 * node + 2].combine(data);
            }
            return;
        }
        
        int mid = s + (e - s) / 2;
        update_range(2 * node + 1, s, mid, l, r, data);
        update_range(2 * node + 2, mid + 1, e, l, r, data);
        m_Tree[node].merge(m_Tree[2 * node + 1], m_Tree[2 * node + 2]);
    }

    SegmentType range_query(const int node, const int s, const int e, const int l, const int r)
    {
        if (m_Lazy[node].has_update())
            propagation(node, s, e);
        
        if (r < s || e < l)
            return SegmentType();
        if (l <= s && e <= r)
            return m_Tree[node];
        
        int mid = s + (e - s) / 2;
        SegmentType res;
        SegmentType left = range_query(2*node + 1, s, mid, l, r);
        SegmentType right = range_query(2 * node + 2, mid + 1, e, l, r);
        res.merge(left, right);
        return res;
    }

public:
    LazySegmentTree() = default;
    ~LazySegmentTree() = default;

    explicit LazySegmentTree(const int sz) : m_SZ(sz), m_Tree(4 * sz), m_Lazy(4 * sz) 
    {
        // build
    }

    void update(const int i, const int data)
    {
        update_element(0, 0, m_SZ - 1, i, data);
    }

    void update(const int l, const int r, const int data)
    {
        update_range(0, 0, m_SZ - 1, l, r, data);
    }

    SegmentType range(const int l, const int r)
    {
        return range_query(0, 0, m_SZ - 1, l , r);
    }
}
```

## Implementation - Iterative

지금 까지 증명과 구현은 재귀 기반으로 이루어 졌다.  
반복 기반의 방식은 기본적으로 `Bottom Up` 방식으로, 접근 시, 구간 $\text{[l, r)}$ 에 접근 할 때의 상황을 생각해보자.

### 항상 구간의 경계 $l$ 또는 $r$ 을 경계값으로 갖는 최대 크기의 `Segment` 를 선택하는 방식이 최적이다

위의 사실은 일반적인 반복기반 `SegmentTree` 의 작동 방식과 일치한다.  
최적의 `Segment` 선택 과정을 귀납적으로 생각해보자.  

선택된 홀수 인덱스 노드는 $/2$ 되기 전 **경로상의 노드** 또는 **그 노드의 오른 자식** 이다.  
그 뒤 /2 하면 반드시 **경로상의 노드** 이거나 다시 **더 상위 노드의 오른 자식** 이 된다.  
선택된 짝수 인덱스 또한 위와 같다.  

위의 방식대로 선택된 `Segment` 들은 즉시 최신화가 가능하나, 선택된 `Segment` 들의 조상들과 후손들은 최신화가 되지 못한다.  
중간의 내부 정점으로 부터 조상과 후손 방향으로 2가지 방향의 지연 전파를 구현해야 한다.  

- 조상으로의 전파
  - 구간 $\text{[l, r)}$ 에서 $l$ 과 $r$ 을 경계값으로 갖는 `Leaf` 에서부터 `root` 까지의 경로상의 `Segment` 를 갱신한다.  
  - 이때, 구간 업데이트는 반드시 해당 `Segment` 또는 왼쪽 또는 오른자식에 포함되어 있다.
  - 해당 `Segment` 를 자식의 `merge` 연산과 더 이전에 누적해온 `lazy` 를 함께 적용하여 최신화를 $O(logN)$ 복잡도로 수행할 수 있다.
- 후손으로의 전파
  - 위의 조상으로의 전파에서 알 수 있듯이, 재귀기반에서와 달리 `lazy` 는 **자기 자신이 아닌, 자식이 수행해야할 UPDATE 정보** 를 의미한다.
  - 재귀 기반의 기본적인 아이디어와 마찬가지로, 질의 구간에 해당되는 경우만 최신화를 수행하면 된다.
  - 단, `lazy` 가 자식이 전파 받아야할 정보 이므로, `leaf index >> H` 부터 `leaf` 로의 방향으로 전파를 수행해야 한다.

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long int;

struct LazyNode
{
    int delta = 0;
    LazyNode() = default;
    inline bool has_update(void) const
    { return delta != 0; }
    inline void combine(const LazyNode &p)
    { this->delta += p.delta; }
    inline void combine(const int data)
    { this->delta += data; }
    inline void reset(void)
    { this->delta = 0; }
};
struct Segment
{
    ll sum = 0;
    int range = 1;
    int min_data = numeric_limits<int>::max();
    int max_data = numeric_limits<int>::min();
    Segment() = default;
    void update_segment(const int data)
    {
        this->sum = data;
        this->max_data = data;
        this->min_data = data;
    }
    void merge(const Segment &L, const Segment &R)
    {
        this->sum = L.sum + R.sum;
        this->min_data = min(L.min_data, R.min_data);
        this->max_data = max(L.max_data, R.max_data);
        this->range = L.range + R.range;
    }
    void apply(const LazyNode &lazy)
    {
        this->sum += 1LL * lazy.delta * range;
        this->min_data += lazy.delta;
        this->max_data += lazy.delta;
    }
    void apply(const int data)
    {
        this->sum += 1LL * data * range;
        this->min_data += data;
        this->max_data += data;
    }
};

template<typename SegmentType, typename LazyNode>
class LazySegmentTree
{
private:
    vector<SegmentType> m_Tree;
    vector<LazyNode> m_Lazy;
    int m_SZ;
    int m_Height;

    inline void lazy_propagate(const int i)
    {
        m_Tree[i].apply(m_Lazy[i >> 1]);
        if (i < m_SZ)
            m_Lazy[i].combine(m_Lazy[i >> 1]);
    }

    inline void instinct_apply(const int i, const int data)
    {
        m_Tree[i].apply(data);
        if (i < m_SZ)
            m_Lazy[i].combine(data);
    }

public:
    LazySegmentTree() = default;
    ~LazySegmentTree() = default;

    explicit LazySegmentTree(const int sz) : m_Height(sizeof(int) * 8 - __builtin_clz(sz)), m_SZ(sz), m_Lazy(sz), m_Tree(2 * sz)
    {
        // build
    }

    void update_element(int i, const int data)
    {
        i += m_SZ;
        m_Tree[i].update_segment(data);
        for (int p = i >> 1; p > 0; p >>= 1)
            m_Tree[p].merge(m_Tree[p << 1], m_Tree[(p << 1) | 1]);
    }

    void push_update(const int leaf)
    {
        for (int p = leaf >> 1; p > 0; p >>= 1)
        {
            m_Tree[p].merge(m_Tree[p << 1], m_Tree[(p << 1) | 1]);
            m_Tree[p].apply(m_Lazy[p]);
        }
    }

    void range_update(int l, int r, const int data)
    {
        l += m_SZ, r += m_SZ;
        int left = l, right = r - 1;
        while(l < r)
        {
            if (l & 1) instinct_apply(l++, data);
            if (r & 1) instinct_apply(--r, data);
            l >>= 1;
            r >>= 1;
        }
        push_update(left);
        push_update(right);
    }

    void pull_update(const int leaf)
    {
        for (int h = m_Height; h > 0; --h)
        {
            int p = leaf >> h;
            if (m_Lazy[p].has_update())
            {
                lazy_propagate(p << 1);
                lazy_propagate((p << 1) | 1);
                m_Lazy[p].reset();
            }
        }
    }

    SegmentType range_query(int l, int r)
    {
        l += m_SZ, r += m_SZ;
        pull_update(l);
        pull_update(r - 1);

        SegmentType res;
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
