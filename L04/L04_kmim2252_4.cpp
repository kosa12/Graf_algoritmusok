// Kosa Matyas, kmim2252, 512
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = 1e2;

void floyd_warshall(vector<vector<int>> &graph, vector<vector<int>> &dist, vector<vector<int>> &next)
{
    int n = graph.size();

    // Kezdetben a távolságokat az élsúlyokkal inicializáljuk.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF)
            {
                next[i][j] = j;
            }
        }
    }

    // Floyd-Warshall algoritmus futtatása.
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

vector<int> get_shortest_path(vector<vector<int>> &next, int start, int end)
{
    vector<int> path;
    if (next[start][end] == -1)
    {
        return path;
    }
    path.push_back(start);
    while (start != end)
    {
        start = next[start][end];
        path.push_back(start);
    }
    return path;
}

int main()
{
    int n, m, start, end;
    cin >> n >> m >> start >> end;

    // Irányított súlyozott gráf szomszédsági mátrixa.
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; i++)
    {
        graph[i][i] = 0;
    }

    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
    }

    // Távolsági és következő pont mátrix inicializálása.
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> next(n + 1, vector<int>(n + 1, -1));

    // Floyd-Warshall algoritmus futtatása.
    floyd_warshall(graph, dist, next);

    cout << "\n\n";

    // Távolsági mátrix kiírása.
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    // Legrövidebb út kiírása.
    vector<int> path = get_shortest_path(next, start, end);
    if (path.empty())
    {
        cout << "Nincs ut" << endl;
    }
    else
    {
        for (int i = 0; i < path.size(); i++)
        {

            cout << path[i] << " ";
        }
        cout << endl;
    }

    return 0;
}