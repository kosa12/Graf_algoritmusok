// Kosa Matyas, kmim2252, 512
#include <iostream>
#include <vector>

using namespace std;

class Graph
{
    int V, E;

    class Edge
    {
    public:
        int src, dest, weight;
    };

    vector<int> prev;
    vector<Edge> edges;

public:
    vector<int> dist;

    Graph(int, int);

    void addEdge(int, int, int);
    bool BellmanFord(int);
};

Graph::Graph(int V, int E)
{
    this->V = V;
    this->E = E;
    dist.resize(V, 1e9);
    prev.resize(V, -1);
}

void Graph::addEdge(int src, int dest, int weight)
{
    edges.push_back({src, dest, weight});
}

bool Graph::BellmanFord(int start)
{
    dist[start] = 0;
    for (int i = 1; i < V; i++)
    {
        for (auto e : edges)
        {
            if (dist[e.src] != 1e9 && dist[e.dest] > dist[e.src] + e.weight)
            {
                dist[e.dest] = dist[e.src] + e.weight;
                prev[e.dest] = e.src;
            }
        }
    }
}

int main()
{
    int V, E, start;
    cin >> V >> E >> start;
    Graph graph(V, E);

    for (int i = 0; i < E; i++)
    {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }
    if (graph.BellmanFord(start))
    {
        cout << "Van negativ kor" << endl;
    }
    else
    {
        for (int i = 0; i < V; i++)
        {
            if (i != start)
            {
                if (graph.dist[i] == 1e9)
                {
                    cout << "Nincs ut" << endl;
                }
                else
                {
                    cout << graph.dist[i] << endl;
                }
            }
        }
    }
    return 0;
}