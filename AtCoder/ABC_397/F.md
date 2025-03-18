# F - Variety Split Hard

- ABC 397 - C 의 hard 버전이다.
- Time Limit : 2sec
- Memory Limit : 1024MB

## Problem Statement

You are given an integer sequence of length $N$ : $A=(A_1,A_2,…,A_N)$.

When splitting A at two positions into three non-empty (contiguous) subarrays, find **the maximum possible sum of the counts of distinct integers in those subarrays**.

More formally, find the maximum sum of the following three values for a pair of integers $(i,j)$ such that $1≤i<j≤N−1$ :\
the count of distinct integers in $(A_1 ,A_2,…,A_i)$, the count of distinct integers in $(A_i+1,A_i+2,…,A_j)$, and the count of distinct integers in $(A_j+1,A_j+2 ,…,A_N)$.

## Constraints

- $3\leq N \leq 3\times10^5$
- $1 \leq A_i \leq N \; (1 \leq i \leq N)$
- All input values are integers.

## Solution

왼쪽의 **subarray** 를 **$L$**, 중간의 **subarray**를 **$M$**, 오른쪽의 **subarray**를 **$R$** 이라 하자.\
그리고 **subarray** 의 **count of distinct int** 를 **$D(sub\;array)$** 라 하자.

- $D(L)$ 과 $D(R)$ 의 값은 선형 복잡도로 전처리 이후 $O(1)$ 복잡도로 알 수 있다.

$M$ 의 마지막 요소 인덱스 를 $m$, $L$의 마지막 요소 인덱스 를 $l$ 이라 할때, $m + 1$ 에 대해서 아래와 같은 점화식을 세울 수 있다.

- **Case 1:** $A_{m + 1}$ 이 $M_{l+1, m}$ 내에 존재 하지 않는 다면, $M_{l + 1, m + 1} = M_{l + 1, m} + 1$
- **Case 2:** $A_{m + 1}$ 이 $M_{l+1, m}$ 내에 존재 한다면, $M_{l + 1, m + 1} = M_{l + 1, m}$

$l$ 값이 $A_{m + 1}$ 의 **이전에 등장한 $last\; index$** 보다 크다면 **Case 1** 이 적용,\
그렇지 않다면, **Case 2** 가 적용된다.

구간 [0, $m$] 에 대해서, $l < m$ 인 모든 $l$ 에 대해, $F(l, m) = D(L_{0,l}) + D(M_{l + 1,m})$ 이라 하면,\
구간의 확장 [0, $m + 1$] 에 대해, [**$last\; index[A_{m + 1}] + 1$** , $max\;l$] 구간 ($max\;l$ = $max\;m - 1$) 에 $ +1 $ 을 하면,\
연장된 구간 [0, $m + 1$] 에 대해서, $l < m + 1$ 인 모든 $l$ 에 대해, $F(l, m + 1) = D(L_{0,l}) + D(M_{l + 1,m + 1})$ 이 성립된다.

요구하는 정답은 $max(max(L_{0, l} + M_{l + 1, m}) + R_{m + 1, N - 1}) = max(max(F(l, m)) + R_{m + 1, N - 1})$ 이므로

- $0 \leq l < m < N - 1$ 의 유효한 범위
  - $min\; l = 0 \quad min\; m = 1$

구간 [0, $m$] 에서 $max(F(l))$ 을 빠른 시간 내에 찾아야 한다.

$\Rightarrow$ **Segment Tree** 를 이용하여 복잡도 $O(N\;log(N))$ 이내에 해결 할 수 있다.

```cpp
#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>

using namespace std;

constexpr int N_MAX = 3e5;
constexpr int NIL = -1;

class SegmentTree
{
private:
    int m_Capacity;
    vector<int> m_Lazy;
    vector<int> m_Tree;

    inline void lazy_update(const int node, const int s, const int e)
    {
        m_Tree[node] += m_Lazy[node];
        if (s != e)
        {
            m_Lazy[2 * node + 1] += m_Lazy[node];
            m_Lazy[2 * node + 2] += m_Lazy[node];
        }
        m_Lazy[node] = 0;
    }

    void point_add(const int node, const int s, const int e, const int i, const int add)
    {
        if (m_Lazy[node] > 0)
            lazy_update(node, s, e);
        if (s == e)
        {
            m_Tree[node] += add;
        }
        else
        {
            int mid = s + (e - s) / 2;
            if (i <= mid)
                point_add(2 * node + 1, s, mid, i, add);
            else
                point_add(2 * node + 2, mid + 1, e, i, add);

            m_Tree[node] = max(m_Tree[2 * node + 1], m_Tree[2 * node + 2]);
        }
    }

    void range_add(const int node, const int s, const int e, const int l, const int r)
    {
        if (m_Lazy[node] > 0)
            lazy_update(node, s, e);
        if (r < s || e < l)
            return;
        if (l <= s && e <= r)
        {
            m_Tree[node]++;
            if (s != e)
            {
                m_Lazy[2 * node + 1]++;
                m_Lazy[2 * node + 2]++;
            }
        }
        else
        {
            int mid = s + (e - s) / 2;

            range_add(2 * node + 1, s, mid, l, r);
            range_add(2 * node + 2, mid + 1, e, l, r);

            m_Tree[node] = max(m_Tree[2 * node + 1], m_Tree[2 * node + 2]);
        }
    }

    int range_query(const int node, const int s, const int e, const int l, const int r)
    {
        if (m_Lazy[node] > 0)
            lazy_update(node, s, e);
        if (r < s || e < l)
            return 0;
        if (l <= s && e <= r)
            return m_Tree[node];

        int mid = s + (e - s) / 2;

        int left = range_query(2 * node + 1, s, mid, l, r);
        int right = range_query(2 * node + 2, mid + 1, e, l, r);

        return max(left, right);
    }

public:
    SegmentTree() = default;
    ~SegmentTree() = default;

    explicit SegmentTree(const int N) : m_Capacity(N), m_Tree(4 * N, 0), m_Lazy(4 * N, 0)
    {
    }

    void addition(const int i, const int val)
    {
        point_add(0, 0, m_Capacity - 1, i, val);
    }

    void range_increase(const int l, const int r)
    {
        range_add(0, 0, m_Capacity - 1, l, r);
    }

    int find_max(const int l, const int r)
    {
        return range_query(0, 0, m_Capacity - 1, l, r);
    }
};

vector<int> A;
vector<int> last_index;
vector<int> L;
vector<int> R;

void read_input(int &N)
{
    cin >> N;
    A.resize(N);
    L.resize(N, 0);
    R.resize(N, 0);
    last_index.resize(N + 1, NIL);
    for (int i = 0; i < N; ++i)
        cin >> A[i];
}

void preprocess(const int N)
{
    set<int> s;
    for (int l = 0; l < N; ++l)
    {
        s.insert(A[l]);
        L[l] = s.size();
    }
    s.clear();
    for (int r = N - 1; r >= 0; --r)
    {
        s.insert(A[r]);
        R[r] = s.size();
    }
}

int find_optimal(const int N)
{
    SegmentTree seg_tree(N);
    // leaf node := L[0, i] + M[i + 1, m]
    for(int i = 0; i < N; ++i)
        seg_tree.addition(i, L[i]);

    int total_max = 0;
    for (int m = 1; m < N - 1; ++m)
    {
        int l_end = m - 1;
        if (last_index[A[m]] != NIL)
            seg_tree.range_increase(last_index[A[m]], l_end); // L이 last_index[A[m]] 까지 포함한 구간부터 1 증가
        else 
            seg_tree.range_increase(0, l_end);  // 모든 L에 대해 1 증가
        
        last_index[A[m]] = m;
        int cur_max = seg_tree.find_max(0, l_end) + R[m + 1];
        total_max = max(total_max, cur_max);
    }

    return total_max;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    read_input(N);

    preprocess(N);

    cout << find_optimal(N);

    return 0;
}
```
