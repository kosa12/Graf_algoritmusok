// Kosa Matyas, 512

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <set>

using namespace std;

ifstream f("1_be.txt");
ofstream o("1_ki.txt");

const int INF = 2e9;

int bfs(vector<vector<int>> &residual_graph, int source, int sink, vector<int> &parent)
{
    int n = residual_graph.size();
    parent.assign(n, -1);

    queue<pair<int, int>> q;
    q.push({source, INF});

    while (!q.empty())
    {
        int u = q.front().first;
        int min_flow = q.front().second;
        q.pop();

        for (int v = 0; v < n; ++v)
        {
            if (parent[v] == -1 && residual_graph[u][v] > 0)
            {
                parent[v] = u;
                int new_flow = min(min_flow, residual_graph[u][v]);

                if (v == sink)
                {
                    return new_flow;
                }

                q.push({v, new_flow});
            }
        }
    }

    return 0;
}

void dfs(vector<vector<int>> &residual_graph, int u, vector<bool> &visited)
{
    visited[u] = true;
    for (int v = 0; v < residual_graph.size(); ++v)
    {
        if (!visited[v] && residual_graph[u][v] > 0)
        {
            dfs(residual_graph, v, visited);
        }
    }
}

pair<int, set<pair<int, int>>> edmonds_karp(vector<vector<int>> &graph, int source, int sink)
{
    int n = graph.size();
    vector<vector<int>> residual_graph = graph;

    int max_flow = 0;
    vector<int> parent(n);

    while (int flow = bfs(residual_graph, source, sink, parent))
    {
        max_flow += flow;
        int u = sink;

        while (u != source)
        {
            int prev_u = parent[u];
            residual_graph[prev_u][u] -= flow;
            residual_graph[u][prev_u] += flow;
            u = prev_u;
        }
    }

    vector<bool> visited(n, false);
    dfs(residual_graph, source, visited);

    set<pair<int, int>> min_cut;
    for (int u = 0; u < n; ++u)
    {
        if (visited[u])
        {
            for (int v = 0; v < n; ++v)
            {
                if (!visited[v] && graph[u][v] > 0)
                {
                    min_cut.insert({u, v});
                }
            }
        }
    }

    return {max_flow, min_cut};
}

int main()
{
    int n;
    f >> n;

    int source, sink;
    f >> source >> sink;

    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));

    int u, v, capacity;
    while (f >> u >> v >> capacity)
    {
        graph[u][v] = capacity;
    }

    auto result = edmonds_karp(graph, source, sink);

    o << "Maximal flow: " << result.first << endl;
    o << "Minimal cut: ";
    for (auto it = result.second.begin(); it != result.second.end(); ++it)
    {
        o << it->first << " " << it->second;
        if (next(it) != result.second.end())
        {
            o << "; ";
        }
    }
    o << endl;

    return 0;
}