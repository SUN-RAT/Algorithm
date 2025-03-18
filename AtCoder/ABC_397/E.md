# E - Path Decomposition of a Tree

- Time Limit : 2sec
- Memory Limit : 1024MB

## Problem Statement

You are given a tree with NK vertices. The vertices are numbered 1,2,…,NK, and the i-th edge (i=1,2,…,NK−1) connects vertices $u_i$ and $v_i$ bidirectionally.

Determine whether this tree can be decomposed into N paths, each of length K.

## Constraints

- $1 \leq N$
- $1 \leq K$
- $NK \leq 2*10^5$
- $1 \leq u_i < v_i \leq NK$
- Given Graph is a tree.
- All input values are integers.

## Solution

- tree 의 모든 정점이 길이가 $K$인 경로 $N$ 개로 분할 될려면, tree의 모든 $leaf\;node$들은 전부 임의의 $path$의 양단 중 하나에 속한다.
- $leaf\;node$ 가 속한 $path$ 에서 임의의 정점이 가장 낮은 깊이 (가장 높은 위상) 을 가지며, 원본 tree에서 해당 정점을 $root$ 로 하는 $sub\;tree$ 가 바로 그 $path$ 이다.
  - 해당 $sub\;tree$ 에서, $root$를 제외한 모든 $node$ 들은 반드시 경로에 기여한 자식의 수가 1 이하 이어야 한다.
    - $root$ 정점은 기여한 자식의 수가 2 이하 이어야 한다.
  - 적절한 $path$ 를 제거 시, $root$ 의 $parent$ 가 있다면, $parent$ 에 대해 연결을 해제 하여 다른 경로 탐색에 대해 무결성 유지.

### 입력으로 주어지는 tree는 항상 id가 작은 정점이 부모가 아닐 수 있음을 주의 하자$...$

```cpp
#include <iostream>
#include <array>
#include <vector>
#include <queue>
#include <set>
#include <limits>
#include <algorithm>

using namespace std;

constexpr int VER_LMT = 2e5;
constexpr int NIL = -1;
constexpr int ROOT = 0;

constexpr const char *POS = "Yes";
constexpr const char *NEG = "No";

struct Node
{
    int parent = NIL;
    int path_child_cnt = 0;
    int sub_size = 1;
    set<int> children;
    Node() = default;
};

array<vector<int>, VER_LMT> graph;
vector<Node> tree;

void read_input(int &N, int &K)
{
    cin >> N >> K;
    int u, v;
    for (int _ = 1; _ < N * K; ++_)
    {
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
}

void refine_tree(const int node_cnt)
{
    tree.resize(node_cnt);
    vector<bool> visit(node_cnt, false);
    queue<int> que;

    que.push(ROOT);
    visit[ROOT] = true;

    while (!que.empty())
    {
        int cur = que.front();
        que.pop();

        for (const int adj : graph[cur])
            if (!visit[adj])
            {
                tree[cur].children.insert(adj);
                tree[adj].parent = cur;
                que.push(adj);
                visit[adj] = true;
            }
    }
}

bool is_possible(const int N, const int K)
{
    queue<int> que;
    // 초기상태, leaf node 만을 경로의 시작점으로 구성
    for (int i = 0; i < N * K; ++i)
        if (tree[i].children.empty())
            que.push(i);

    int partitioned_cnt = 0;
    while (!que.empty())
    {
        int cur = que.front();
        que.pop();

        // tree[id].sub_size := 자기 자신을 포함한 자기 자신이 root 일 때의 sub tree 정점의 수
        if (tree[cur].sub_size == K)
        { // 경로의 길이 K 완성
            if (tree[cur].path_child_cnt > 2) // 경로의 조건 만족 X
                return false;
                
            partitioned_cnt++;
            int parent = tree[cur].parent;
            if (parent != NIL)
            {
                tree[parent].children.erase(cur);
                if (tree[parent].children.empty())
                    que.push(parent);
            }
        }
        else if (tree[cur].sub_size < K)
        {
            if (tree[cur].path_child_cnt > 1) // 경로의 조건 만족 X
                return false;

            int parent = tree[cur].parent;
            if (parent == NIL) // 경로의 길이가 K 보다 작은 경로가 필수적으로 생성
                return false;

            tree[parent].sub_size += tree[cur].sub_size;
            tree[parent].path_child_cnt++;
            tree[parent].children.erase(cur);
            if (tree[parent].children.empty())
                que.push(parent);
        }
        else // 경로의 길이가 K 초과한 경로가 필수적으로 생성
            return false;
    }

    return partitioned_cnt == N;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, K;
    read_input(N, K);

    refine_tree(N * K);

    cout << (is_possible(N, K) ? POS : NEG);

    return 0;
}
```
