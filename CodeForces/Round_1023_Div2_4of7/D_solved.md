# D. Apple Tree Traversing

- Time limit : 5 seconds
- Memory limit : 512 megabytes

## Problem Statement

There is an apple tree with $N$ nodes, initially with one apple at each node. You have a paper with you, initially with nothing written on it.

You are traversing on the apple tree, by doing the following action as long as there is at least one apple left:

- Choose an apple path $(u,v)$. A path $(u,v)$ is called an apple path if and only if for every node on the path $(u,v)$, there's an apple on it.

- Let $d$ be the number of apples on the path, write down three numbers $(d,u,v)$, in this order, on the paper.

- Then remove all the apples on the path $(u,v)$.

Here, the path $(u, v)$ refers to the sequence of vertices on the unique shortest walk from $u$ to $v$.

Let the number sequence on the paper be $a$. Your task is to find the lexicographically largest possible sequence $a$.

## Input

- Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
- The first line of each test case contains a number $N$ ($1 \le N \le 1.5 \cdot 10^5$).
- The following $N-1$ lines of each test case contain two numbers $u,v$ ($1 \le u,v \le N$). It's guaranteed that the input forms a tree.
- It is guaranteed that the sum of $N$ over all test cases does not exceed $1.5 \cdot 10^5$.

## Output

- For each test case, output the lexicographically largest sequence possible $a_1, a_2, \ldots, a_{|a|}$. It can be shown that $|a| \le 3 \cdot N$.

## Solution

$Tree$ 에 대한 `seq` 가 사전순 으로 가장 큰 `seq` 가 될려면, 매 순간 삭제하는 $path$ 의 길이 값 $d$ 가 최대인 $path$ 를 우선적으로 선택 하면 된다.  
최대값 $d$ 인 경로가 2개 이상 인 경우, $path$ 의 끝점 $u, v$ 중 큰 값이 더 큰 $path$ 를 우선적으로 선택 하여 삭제 하면 사전순 으로 가장 큰 `seq` 를 구할 수 있다.  

### $Tree$ 에서 가장 긴 경로 찾기

$Tree$ 에서 가장 긴 경로는 $Tree$ 의 $Diameter$ 이다.  
$Tree$ 의 직경 길이를 2 번의 `BFS` 를 통해 구할 수 있고,  
가장 적절한 $u, v$ 쌍 또한 `BFS` 과정에서 구할 수 있다.  

이 후의 문제는, 해당 경로가 삭제된 이후의 잔여 $Tree$ 를 어떻게 관리할 것인지 생각해야 한다.  

### $Tree$ Component 관리

초기 입력으로 주어진 $Tree$ 는 하나의 비순환 연결 그래프 임이 보장되어 있으므로, 초기의 $Tree$ 는 1개 이다.  

해당 $Tree$ 에서 적절한 경로를 찾아 삭제한 직후를 생각해보자.  

- 해당 경로에 속한 임의의 정점 $i$ 가 삭제
  - $i$ 의 자식들 중 경로에 속하지 않은 자식들은 모두 경로 삭제로 생성된 $Tree$ 의 $root$ 가 된다.  
  - $i$ 의 부모 정점은 반드시 삭제된 경로에 속하므로 추가로 고려할 사항이 없다.  
  - 삭제된 정점 $i$ 는 다른 인접한 정점들과 모두 연결이 끊어져야 한다.

위의 분할을 생각하며, $Tree$ 의 분할을 구현해야 한다.  

### `Seq` 구성

하나의 $Tree$ 에서 단 하나의 적절한 $path$ 만이 선택된다. 그리고, 임의의 $Tree$ 에서의 선택과 삭제는 다른 $Tree$ 에 영향이 없으므로, 분할로 생성된 $Tree$ 의 순서대로 $path$ 를 모두 구한 뒤, 내림차순 으로 정렬 해도 지장이 없다.  

```cpp
using Record = array<int, 3>;

constexpr int N_MAX = 150'000;
constexpr int NIL = -1;

array<set<int>, N_MAX + 1> Tree;
array<int, N_MAX + 1> Before;

pii BFS(const int root)
{
    int len = 0;
    int max_end = NIL;
    queue<int> que; que.push(root);
    Before[root] = NIL;
    while (!que.empty())
    {
        ++len;
        int width = que.size();
        int max_id = NIL;
        while (width-- > 0)
        {
            int cur = que.front(); que.pop();
            max_id = max(max_id, cur);
            for (const int adj : Tree[cur])
                if (adj != Before[cur])
                {
                    Before[adj] = cur;
                    que.push(adj);
                }
        }

        if (que.empty()) max_end = max_id;
    }
    return make_pair(max_end, len);
}

void apply_partition(queue<int> &component, int node)
{
    int after = NIL;
    while (node != NIL)
    {
        for (const int adj : Tree[node])
            if (adj != after && adj != Before[node])
            {
                Tree[adj].erase(node);
                component.push(adj);
            }
        
        Tree[node].clear();
        after = node;
        node = Before[node];
    }
}

void solve(void)
{
    int N;
    cin >> N;

    int u, v;
    for (int _ = 1; _ < N; ++_)
    {
        cin >> u >> v;
        Tree[u].insert(v), Tree[v].insert(u);
    }

    vector<Record> seq; seq.reserve(N);
    queue<int> component; component.push(1);
    while (!component.empty())
    {
        int tree_cnt = component.size();
        while (tree_cnt-- > 0)
        {
            int node = component.front(); component.pop();

            auto [s, len] = BFS(node);
            auto [e, diameter] = BFS(s);

            seq.push_back({diameter, max(s, e), min(s, e)});
            apply_partition(component, e);
        }
    }

    sort(seq.begin(), seq.end(), greater<Record>());

    for (const auto &[d, u, v] : seq) cout << d << ' ' << u << ' ' << v << ' ';
    cout << ENDL;
}
```

## Better Solution

다른 제출한 사람의 결과가 고작 몇백 ms 밖에 되지 않아 (위의 풀이는 1600 ms) 해당 사람의 풀이를 참고한 풀이 이다.  

어떻게든 경로를 삭제하든지 간에, 해당 경로는 원본 $Tree$ 의 경로 이다.  
따라서, 분할 이후 $Tree$ 들의 직경 경로 또한 원본 $Tree$ 의 경로에 포함되어 있으며,  
모든 가능한 최대 직경 경로 중 최적의 경로를 선택 시, 해당 경로가 속한 $Tree$ 에서 현 시점에서도 유효한 지 선별만 하면 쉽게 `seq` 를 구축할 수 있다.  

```cpp
#define Heap std::priority_queue

using Record = array<int, 4>;

constexpr int N_MAX = 150'000;
constexpr int NIL = -1;

array<vector<int>, N_MAX + 1> Tree;
array<int, N_MAX + 1> Before;
array<set<pii>, N_MAX + 1> Best;
array<bool, N_MAX + 1> Apple;

void DFS(const int N)
{
    vector<pair<int, bool>> pre_alloc; pre_alloc.reserve(N);
    stack<pair<int, bool>, vector<pair<int, bool>>> stk(move(pre_alloc));

    Before[1] = NIL;
    stk.emplace(1, false);
    while (!stk.empty())
    {
        auto [node, completed] = stk.top();
        if (completed)
        {
            stk.pop();
            if (Before[node] != NIL)
            {
                auto [mx_len, leaf] = *Best[node].rbegin();
                Best[Before[node]].emplace(mx_len + 1, leaf);
            }
        }
        else
        {
            stk.top().second = true;
            Best[node].emplace(1, node);
            for (const int adj : Tree[node])
                if (adj != Before[node])
                {
                    Before[adj] = node;
                    stk.emplace(adj, false);
                }
        }
    }
}

Record compute_best(const int node)
{
    if (Best[node].size() == 1) return {1, node, node, node};

    auto it = Best[node].rbegin();
    auto [len_a, a] = *it;
    auto [len_b, b] = *(++it);
    return {len_a + len_b - 1, max(a, b), min(a, b), node};
}

void solve(void)
{
    int N; cin >> N;
    fill(Tree.begin() + 1, Tree.begin() + 1 + N, vector<int> {});
    fill(Best.begin() + 1, Best.begin() + 1 + N, set<pii> {});
    fill(Apple.begin() + 1, Apple.begin() + 1 + N, true);

    int u, v;
    for (int _ = 1; _ < N; ++_)
    {
        cin >> u >> v;
        Tree[u].push_back(v), Tree[v].push_back(u);
    }

    DFS(N);
    vector<Record> pre_alloc; pre_alloc.reserve(N);
    Heap<Record, vector<Record>, less<Record>> max_heap(less<Record>(), move(pre_alloc));
    for (int i = 1; i <= N; ++i)
        max_heap.emplace(compute_best(i));

    while (!max_heap.empty())
    {
        auto [diameter, u, v, node] = max_heap.top(); max_heap.pop();
        if (!Apple[node] || compute_best(node) != Record{diameter, u, v, node})
            continue;
        
        cout << diameter << ' ' << u << ' ' << v << ' ';

        while (u != node) Apple[u] = false, u = Before[u];
        while (v != node) Apple[v] = false, v = Before[v];
        Apple[node] = false;

        auto [len, leaf] = *Best[node].rbegin();
        while (Before[node] != NIL && Apple[Before[node]] && Best[Before[node]].count({++len, leaf}))
        {
            int prev = Before[node];
            Record before = compute_best(prev);
            Best[prev].erase({len, leaf});
            Record after = compute_best(prev);
            if (after != before)
            {
                max_heap.emplace(after);
                if (Before[prev] != NIL && Apple[Before[prev]])
                {
                    auto [another_len, another_leaf] = *Best[prev].rbegin();
                    Best[Before[prev]].emplace(another_len + 1, another_leaf);
                }
                node = prev;
            }
            else break;
        }
    }
    cout << ENDL;
}
```
