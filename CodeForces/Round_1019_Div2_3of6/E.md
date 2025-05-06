# E. Keep the Sum

- Time limit : 2.5 seconds
- Memory limit : 256 megabytes

## Problem Statement

You are given an integer $k$ and an array $a$ of length $n$, where each element satisfies $0 \le a_i \le k$ for all $1 \le i \le n$. You can perform the following operation on the array:

- Choose two distinct indices $i$ and $j$ ($1 \le i,j \le n$ and $i \neq j$) such that $a_i + a_j = k$.

- Select an integer $x$ satisfying $-a_j \le x \le a_i$.

- Decrease $a_i$ by $x$ and increase $a_j$ by $x$. In other words, update $a_i := a_i - x$ and $a_j := a_j + x$.

Note that the constraints on $x$ ensure that all elements of array $a$ remain between $0$ and $k$ throughout the operations.

Your task is to determine whether it is possible to make the array $a$ non-decreasing-  using the above operation. If it is possible, find a sequence of at most $3n$ operations that transforms the array into a non-decreasing one.

It can be proven that if it is possible to make the array non-decreasing using the above operation, there exists a solution that uses at most $3n$ operations.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
- The first line of each test case contains two integers, $n$ and $k$ ($4 \le n \le 2 \cdot 10^5$, $1 \le k \le 10^9$) — the length of the array $a$ and the required sum for the operation.
- The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($0 \le a_i \le k$) — the elements of array $a$.
- It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

## Output

- For each test case, output $-1$ if it is not possible to make the array non-decreasing using the operation.
- Otherwise, output the number of operations $m$ ($0 \le m \le 3n$). On each of the next $m$ lines, output three integers $i$, $j$, and $x$ representing an operation where $a_i$ is decreased by $x$ and $a_j$ is increased by $x$.
- Note that you are not required to minimize the number of operations. If there are multiple solutions requiring at most $3n$ operations, you may output any.

## Upsolving

- 풀이의 코드는 $O(N logN)$ 의 상수배 복잡도를 가지고 있다. 문제의 입력 제한인 $2*10^5$ 대헤 시간 이내에 동작할 것으로 생각 했으나, 8번째 test case 에서 `TLE` 를 받음..
- 풀이의 로직은 맞지만, 최적화에서 실패한 문제.. (아직 최적화한 풀이 X)

문제의 `operation` 을 살펴보자.  

$a_i + a_j = K$ 이면, $a_i = a_i - x$ , $a_j = a_j + x$ 로 의 연산이 가능하다.  
$x \in [-a_j, a_i]$ 이므로, 연산 이후의 $a_i$ 와 $a_j$ 는 아래의 범위를 만족 한다.  
연산 이전의 $a_i$ 를 $prev_i$ , $a_j$ 를 $prev_j$ 라 하면,  
$a_i \in [prev_i - prev_i, prev_i + prev_j] \equiv [0, K]$  
$a_j \in [prev_j - prev_j, prev_j + prev_i] \equiv [0, K]$  

즉, 조건을 만족하는 $a_i$ 와 $a_j$ 에 대해, 둘 중 하나를 원하는 값으로 변경할 수 있다.  
따라서, 조건을 만족하는 `pair` 가 단 하나도 존재하지 않고, 입력된 배열이 `non - decreasing` 을 만족하지 않으면,  
수정이 불가능 하므로, 해당 입력은 절대로 문제의 요구를 만족할 수 없는 불가능한 case 라고 판단할 수 있다.  

입력 자체만으로 `non - decreasing` 을 만족하는 경우, 연산을 하지 않아도 되므로, `pair` 가 최소한 하나는 존재하고 `non - decreasing` 을 만족하지 않는 입력에 대해 생각해 보자.  

먼저, `non - decreasing` 을 만족할려면,  
모든 $i \in [0, N - 1]$ 에 대해서, $a_i = min(Array[i : N - 1])$ 을 만족 해야 한다.  

$a_i \neq min(Array[i : N - 1])$ 이라면, 연산의 과정을 통해 최소값을 가지도록 변경 해야 한다.  
아래의 가정을 만족한다고 하자.  

- $a_l + a_r = K$ , $l = 0$ , $r = N - 1$
- $a_m = min(Array[i : N - 2])$
  - 첫 번째 가정으로, $a_0$ 과 $a_{N-1}$ 은 언제든지 값 수정이 가능하므로, 양 끝단은 제외

1. $a_l$ 에 $a_m$ 값을 할당 한다. $\rightarrow$ 이제, $a_m + a_r = K$ 를 만족 한다.
2. $a_m$ 에 $a_i$ 값을 할당 한다. $\rightarrow$ 이제, $a_i + a_r = K$ 를 만족 한다.
3. $a_i$ 에 초기의 $a_i$ 값, 즉 사전에 구한 $min(Array[i : N - 1])$ 값을 할당 한다. $\rightarrow$ 이제, $a_l + a_r = K$ 를 다시 만족 한다.

위와 같이 3번의 연산으로 $a_i$ 를 잔여 구간의 최소값으로 변경 할 수 있다.  

입력으로 주어진 모든 $a_i \in [0, K]$ 이므로, 순회 이후, $a_0 = 0$ , $a_{N - 1} = K$ 로 수정하면,  
연산 이후의 배열은 `non - decreasing` 의 성질을 만족한다.  

위 방식의 연산 횟수가 $3N$ 을 초과하는지 검토해보자.  

1. 임의의 `pivot pair` 가 $(0, N - 1)$ 이 아닌 경우, $l$ 을 0 으로 보정 하는 연산 1회, $r$ 을 $N - 1$ 로 보정하는 연산 1회, 최대 2번의 연산을 수행하게 된다.  
2. 구간 $[1, N - 2]$ 에서 최대 $3$ 번의 연산을 수행하게 된다.  
3. 구간 순회 이후 양 끝단의 값 수정으로 $1$ 번의 연산을 수행한다.  

총 연산 횟수는 최대 $2 + 3 * (N - 2) + 1 < 3*N$ 으로, 문제의 조건을 만족 한다.  

구간의 최소값과 해당 값을 지닌 인덱스를 찾는 구간 최소 쿼리는 `Segment Tree` 를 이용하면, $O(log N)$ 의 복잡도로 해결 할 수 있으므로 최종 복잡도는 $O(N log N)$ 이다.  

*그러나 어째서인지 8번 test case 에서 계속 TLE 를 남발한다...*

```cpp
constexpr int N_MAX = 2e5;
constexpr int INF = numeric_limits<int>::max();

struct Query
{
    int i;
    int j;
    int x;
    Query() = default;
    Query(const int _i, const int _j, const int _x) : i(_i), j(_j), x(_x) {}
};

static inline void merge(pii &p, const pii &left, const pii &right)
{ p = (left.second > right.second) ? right : left; }

static inline void merge(pii &res, const pii &other)
{ if (res.second > other.second) res = other; }

class SegmentTree
{
private:
    int m_SZ;
    vector<pii> m_Tree;

public:
    SegmentTree() = default;
    ~SegmentTree() = default;

    void build_tree(const int sz, const int *A)
    {
        m_SZ = sz;
        m_Tree.resize(2 * sz, make_pair(-1, INF));

        for (int i = 0; i < sz; ++i)
            m_Tree[i + sz] = make_pair(i, A[i]);
        for (int p = sz - 1; p > 0; --p)
            merge(m_Tree[p], m_Tree[p << 1], m_Tree[(p << 1) | 1]);
    }

    void update(const int i, const int data)
    {
        m_Tree[i + m_SZ] = make_pair(i, data);
        for (int p = (i + m_SZ) >> 1; p > 0; --p)
            merge(m_Tree[p], m_Tree[p << 1], m_Tree[(p << 1) | 1]);
    }

    pii range(int l, int r)
    {
        pii res(-1, INF);
        l += m_SZ, r += m_SZ;
        while (l < r)
        {
            if (l & 1) merge(res, m_Tree[l++]);
            if (r & 1) merge(res, m_Tree[--r]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};

int A[N_MAX];
SegmentTree ST;
vector<Query> Answer(3 * N_MAX);

int N, K;

void operation(int &i, int l, int r, const int res)
{
    int x = A[l] - res;
    Answer[i++] = Query(l + 1, r + 1, x);
}

void solve(void)
{
    cin >> N >> K;

    int prev = -1;
    bool non_decrease = true;
    map<int, int> mp;
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
        if (A[i] < prev)
            non_decrease = false;
        prev = A[i];
        mp[A[i]] = i;
    }

    int l = -1, r = -1;
    for (int i = 0; i < N; ++i)
        if (mp.find(K - A[i]) != mp.end())
            if (mp[K - A[i]] != i)
            {
                l = i;
                r = mp[K - A[i]];
                break;
            }

    if (!non_decrease && l == -1 && r == -1)
        cout << -1 << ENDL;
    else if (non_decrease)
        cout << 0 << ENDL;
    else
    {
        int cnt = 0;
        if (l != 0)
        {
            operation(cnt, l, r, A[0]);
            A[l] = A[0];
            A[r] = K - A[0];
            // A[1] + A[r] = K
            l = 0;
        }
        if (r != N - 1)
        {
            operation(cnt, l, r, K - A[N - 1]);
            A[l] = K - A[N - 1];
            A[r] = A[N - 1];
            // A[1] + A[N] = K
            r = N - 1;
        }

        ST.build_tree(N, A);
        for (int s = 1; s < r; ++s)
        {
            auto [min_id, min_data] = ST.range(s, r);
            if (s == min_id)
                continue;
            operation(cnt, l, r, min_data);
            operation(cnt, min_id, r, A[s]);
            operation(cnt, s, r, min_data);
            A[min_id] = A[s];
            ST.update(min_id, A[s]);
        }
        operation(cnt, l, r, 0);

        cout << cnt << ENDL;
        for (int i = 0; i < cnt; ++i)
            cout << Answer[i].i << ' ' << Answer[i].j << ' ' << Answer[i].x << ENDL;
    }
}
```
