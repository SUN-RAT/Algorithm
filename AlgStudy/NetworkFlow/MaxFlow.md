# Network Flow - Max Flow

지도상에서 도시를 정점으로, 도로를 간선으로 간주하여 지도를 방향그래프로 모델링 할 수 있는 것 처럼, 시스템 내에서 `mass` 의 이동을 방향 그래프로 모델링 할 수 있다.  

다만, `mass` 의 흐름을 위해 `Capacity` 와 `Flow` 라는 개념이 추가되며, 흐름의 출발 정점 `Source` $s$ , 도착 정점 `Sink` $t$ 가 존재한다고 가정한다.

방향 그래프로의 모델링 시, 관찰되는 특징은 아래와 같다.

- **용량 제약 조건**
  - 정점 $u$ 에서 $v$ 를 연결하는 $\text{edge(u, v)}$ 가 존재 할 때,  
  $\text{edge(u, v)}$ 는 최대 보낼 수 있는 용량 `Capacity` $\text{Cap(u, v)}$ 가 할당 되어 해당 값 이하의 `Flow` 를 보낼 수 있다.

- **Flow Conservation 유량 보존**
  - `Source` 와 `Sink` 를 제외한 정점 (이하 중간 정점) 에서 `mass` 는 **정점에 쌓이지 않고, 그 정점을 통과하여 흐른다** .  
  - 따라서, `mass` 가 임의의 정점으로 들어가는 `in-Flow` 는 해당 정점에서 나가는 `out-Flow` 와 동일해야 한다.  

- **Skew Symmetry 유량의 대칭성**
  - 모든 정점 쌍 $\text{(u, v)}$ 에 대해 $\text{flow(u, v) = -flow(v, u)}$ 이다.

## Ford-Fulkerson Method

```text
Ford-Fulkerson Method(G, s, t)
모든 Flow 를 0 으로 초기화 한다.
while : 잔여네트워크 G_f 에 증강 경로 p 가 존재
    경로 p 를 따라서 flow f 를 증가시킨다.
return f
```

`Ford-Fulkerson Method` 는 구체적인 증강 경로를 찾는 방법을 명시하지 않지만, 중요한 이론적 기반을 제시하는 방법이다.  

주로 **3가지 아이디어** 에 의존하는데, 아래와 같다.

- `Augmenting Path` 증강 경로
- `Residual Graph` 잔여 그래프
- `Min Cut` 절단

위 3가지 개념이 이론적 토대를 이루고, Edmonds-Karp, Dinic's, Push-Relabel 등의 다양한 파생 알고리즘으로 확장된다.

### `Residual Graph` 잔여 그래프

문제의 목표는 **원천점 $s$ 에서 도착점 $t$ 까지 보낼 수 있는 최대 유량** 을 찾는 것 이다.

*현재 네트워크에서 $\text{Cap}$ 이 남은 간선을 채우면, 최대 유량을 구할 수 있는가 ?*  

이것이 참 인지 알아보자.  
가정 : **포화된 구간이 하나라도 있으면, 그 뒤쪽 경로를 어떻게 바꾸어도 더 이상 전체 유량을 늘릴 수 없다** .  

$G$ 에서 포화된 $s$ 와 가장 가까운 임의의 간선 $\text{edge(u, v)}$ 가 있다.  
현재 유량의 크기를 $Flow_{before}$ 라 하자. 그리고 해당 유량의 하한은 $\text{Cap(u, v)}$ 이다.  
$u$ 에서 이동 가능한 또 다른 정점 $w$ 가 있다면, $\text{flow(u, v)}$ 에서의 일부를 $\text{flow(u, w)}$ 로 옮김으로 더 추가적인 유량의 확보가 가능하다.  
물론, $\text{edge(u, v)}$ 이후의 경로의 용량이 $\Delta \text{flow(u, w)}$ 보다 작은 용량만 있다면, 전체 네트워크의 유량의 증가량은 없다.  
하지만, 유량을 옮김으로써, 손해는 보지 않음이 보장 되므로, **포화된 구간이 있더라도, 이전의 경로 수정으로 전체 유량을 늘릴 수 있다** .

하지만, 모델링 한 네트워크 $G$ 에서는 `포화된 flow(u, v) 의 일부를 감소하겠다` 라는 개념을 표현할 방법이 없다.  

따라서, `Residual Graph` $G_f$ 에선 원본 $G$ 엔 존재하지 않는 `역방향 간선` 을 포함한다.  

원본 $G$ 의 양수 플로우 $\text{flow(u, v)}$ 의 가능한 **감소** 를 나타내기 위해, 최대 $\text{flow(u, v)}$ 를 상쇄할 수 있는 `역방향 플로우` $\text{flow}^{-1} \text{(u, v)}$ 개념이 추가된다.  

그렇다면, `Residual Graph` 의 **잔여용량** $\text{Resi(u, v)}$ 는 아래와 같이 정의할 수 있다.

```math
\text{Resi(u, v)} = 
\begin{cases}
\text{edge(u, v)} \in E \rightarrow \text{Cap(u, v) - flow(u, v)} \\
\text{edge(v, u)} \in E \rightarrow \text{Cap(u, v) - } \text{flow}^{-1} \text{(v, u)} = \text{0 - (-flow(v, u))} = \text{flow(v, u)}\\
\text{Otherwise, 0}
\end{cases}
```

이어서, 원본 네트워크 $G$ 에 잔여 네트워크 $G_f$ 에서 선택한 증강경로 $P$ 에 대해, 얻은 증강 흐름 $flow^*$ 을 기존의 흐름 $flow$ 에 더할때의 상황을 생각해보자.  

- 아직 용량이 남은 정방향 간선에선 증가
- 이미 흘린 흐름을 되돌려야 할 때는 역방향 간선을 이용하여 감소

이 두가지 동작을 한번에 처리하는 것 이다.  
아래의 일반화에서 $flow^*(u, v)$ 는 $G_f$ 의 증강경로 $P$ 에서 $u \rightarrow v$ 로 보내고자 하는 유량 이다.

```math
flow \oplus flow^* = 
\begin{cases}
edge(u, v) \in E \rightarrow flow(u, v) + flow^*(u, v) - flow^(v, u)\\
\text{Otherwise, } flow(u, v)
\end{cases} \\
```

```math
Resi^* = 
\begin{cases}
(u, v) \in P, (u, v) \in E \rightarrow Resi(u, v) - \delta , Resi(v, u) + \delta\\
(v, u) \in P, (u, v) \in E \rightarrow Resi(u, v) + \delta , Resi(v, u) - \delta\\
\text{Otherwise, } Resi(u, v) \text{ , } Resi(v, u)
\end{cases}
```

위와 같이 $G_f$ 의 $Resi$ 가 정방향과 역방향 서로간 대칭적으로 증감 하는 것이 `상쇄 Cancellation` 개념이다.  

### `Augmenting Path` 증강 경로

네트워크 $G$ 와 `Flow` 의 `Augmenting Path` 는 $G_f$ 에서 $s$ 에서 $t$ 로의 **단순 경로** 이다.  

이에 따라 $s$ 에서 $t$ 까지, $G_f$ 에서 $\text{Resi(u, v)} > 0$ 인 간선을 선택하며, 경로 $P$ 의 flow 값이 0 보다 큰 것을 보장한다.  

1. `Source` 에서 `Sink` 까지 $\text{Resi} > 0$ 인 경로를 찾은 뒤
2. 해당 경로를 따라 $flow \oplus flow^*$ 연산을 한다.  

위 과정을 반복하여, `Flow` 가 더 이상 늘지 않을 때, 즉 `Augmenting Path` 가 존재하지 않을 때 `Max Flow` 에 도달하게 된다.  

`Augmenting Path` $P$ 의 각 간선 $flow^*(u, v)$ 또는 $flow^*(v, u)$ 는 $\underset{(u,v)\in P}{min}c_f(u,v)$ 이다.  
따라서, $flow \oplus flow^*$ 일반화를 아래 처럼 표현할 수 있다.

```math
flow \oplus flow^* = 
\begin{cases}
(u, v) \in P, (u, v) \in E \rightarrow flow(u, v) + \delta \\
(v, u) \in P, (u, v) \in E \rightarrow flow(u, v) - \delta \\
\end{cases}
```

## Implementation - Edmonds-Karp Algorithm

`Residual Graph` $G_f$ 에서 증강경로 탐색을 `BFS` 로 수행한다.  

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long int;
using pii = pair<int, int>;

constexpr int INF = numeric_limits<int>::max();

struct Edge
{
    int dest;
    int reverse_id;
    int resi;
    Edge() = default;
    Edge(const int _dest, const int _rev, const int _cap) : dest(_dest), reverse_id(_rev), resi(_cap) {}
};

vector<vector<Edge>> Graph;
vector<pii> Prev;

void preprocess(const int node_cnt, const int edge_cnt)
{
    Graph.assign(node_cnt, vector<Edge> {});

    int u, v, cap;
    for (int e = 0; e < edge_cnt; ++e)
    {
        cin >> u >> v >> cap;
        Graph[u].emplace_back(v, Graph[v].size(), cap);
        Graph[v].emplace_back(u, Graph[u].size() - 1, 0);
    }
}

int BFS(const int s, const int t)
{
    fill(Prev.begin(), Prev.end(), make_pair(-1, -1));
    Prev[s] = make_pair(s, s);

    queue<pii> q; q.emplace(s, INF);
    while (!q.empty())
    {
        auto [cur, flow] = q.front();
        q.pop();

        for (int i = 0; i < Graph[cur].size(); ++i)
        {
            const auto &e = Graph[cur][i];
            if (Prev[e.dest].first == -1 && e.resi > 0)
            {
                Prev[e.dest] = make_pair(cur, i);
                int next_flow = min(flow, e.resi);
                if (e.dest == t)
                    return next_flow;
                else
                    q.emplace(e.dest, next_flow);
            }
        }
    }

    return 0;
}

ll calculate_max_flow(const int n, const int s, const int t)
{
    ll total = 0; int delta;
    Prev.resize(n);

    while (delta = BFS(s, t))
    {
        total += delta;
        int node = t;
        while (node != s)
        {
            auto [prev, edge] = Prev[node];
            Graph[prev][edge].resi -= delta;
            Graph[node][Graph[prev][edge].reverse_id].resi += delta;
            node = prev;
        }
    }

    return total;
}
```
