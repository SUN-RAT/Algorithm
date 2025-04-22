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