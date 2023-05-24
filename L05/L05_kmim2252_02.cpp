// Kosa Matyas, 512

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

ifstream f("2_be.txt");
ofstream o("2_ki.txt");

const int INF = 1e9;

void initializePreflow(vector<vector<int>> &capacity, vector<vector<int>> &flow,
                       vector<int> &excess, vector<int> &height, int source)
{
    int n = capacity.size();
    height[source] = n;
    excess[source] = INF;

    for (int v = 0; v < n; ++v)
    {
        flow[source][v] = capacity[source][v];
        flow[v][source] = -flow[source][v];
        excess[v] = flow[source][v];
    }
}

void push(vector<vector<int>> &capacity, vector<vector<int>> &flow,
          vector<int> &excess, int u, int v)
{
    int delta = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += delta;
    flow[v][u] = -flow[u][v];
    excess[u] -= delta;
    excess[v] += delta;
}

void relabel(vector<vector<int>> &capacity, vector<vector<int>> &flow,
             vector<int> &height, int u)
{
    int min_height = INF;
    int n = capacity.size();
    for (int v = 0; v < n; ++v)
    {
        if (capacity[u][v] - flow[u][v] > 0 && height[v] < min_height)
        {
            min_height = height[v];
        }
    }
    height[u] = min_height + 1;
}

void discharge(vector<vector<int>> &capacity, vector<vector<int>> &flow,
               vector<int> &excess, vector<int> &height, int u)
{
    int n = capacity.size();
    while (excess[u] > 0)
    {
        bool pushed = false;
        for (int v = 0; v < n; ++v)
        {
            if (capacity[u][v] - flow[u][v] > 0 && height[u] == height[v] + 1)
            {
                push(capacity, flow, excess, u, v);
                pushed = true;
            }
        }
        if (!pushed)
        {
            relabel(capacity, flow, height, u);
        }
    }
}

int maxFlow(vector<vector<int>> &capacity, int source, int sink)
{
    int n = capacity.size();
    vector<vector<int>> flow(n, vector<int>(n, 0));
    vector<int> excess(n, 0), height(n, 0);

    initializePreflow(capacity, flow, excess, height, source);

    queue<int> active;
    for (int i = 0; i < n; ++i)
    {
        if (i != source && i != sink && excess[i] > 0)
        {
            active.push(i);
        }
    }

    while (!active.empty())
    {
        int u = active.front();
        active.pop();
        int old_excess = excess[u];
        discharge(capacity, flow, excess, height, u);
        if (excess[u] > 0 && excess[u] < old_excess)
        {
            active.push(u);
        }
    }

    int max_flow = 0;
    for (int i = 0; i < n; ++i)
    {
        max_flow += flow[source][i];
    }
    return max_flow;
}

int main()
{
    int n, source, sink;
    f >> n >> source >> sink;

    vector<vector<int>> capacity(n, vector<int>(n, 0));
    int u, v, c;
    while (f >> u >> v >> c)
    {
        capacity[u - 1][v - 1] = c;
    }

    o << "Maximum flow: " << maxFlow(capacity, source - 1, sink - 1) - 1 << endl;
    return 0;
}