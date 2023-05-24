// Kosa Matyas, kmim2252, 512

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <limits>
#include <fstream>

using namespace std;

const int INF = 1e9;

ifstream f("1.in");
ofstream o("1.out");

typedef pair<int, int> pii;
typedef vector<pii> vp;

void dijkstra(int s, vector<vp> &graph, vector<int> &dist, vector<int> &parent)
{
    dist.assign(graph.size(), INF);
    parent.assign(graph.size(), -1);
    dist[s] = 0;

    set<pii> q;
    q.insert(make_pair(0, s));

    while (!q.empty())
    {
        int v = q.begin()->second;
        q.erase(q.begin());

        for (auto e : graph[v])
        {
            int u = e.first;
            int w = e.second;
            if (dist[u] > dist[v] + w)
            {
                q.erase(make_pair(dist[u], u));
                dist[u] = dist[v] + w;
                parent[u] = v;
                q.insert(make_pair(dist[u], u));
            }
        }
    }
}

void print(int s, int t, const vector<int> &parent)
{
    if (t == s)
    {
        o << s;
        return;
    }
    print(s, parent[t], parent);
    o << " " << t;
}

void print_dist(int s, const vector<int> &dist, const vector<int> &parent)
{
    for (int i = 0; i < dist.size(); i++)
    {
        if (i == s)
            continue;
        o << "A legrovidebb ut hossza " << i << "-ba: ";
        if (dist[i] == INF)
        {
            o << "nem elerheto" << endl;
        }
        else
        {
            o << dist[i] << endl;
        }
        o << "A legrovidebb ut " << s << "-bol " << i << "-ba: ";
        if (dist[i] == INF)
        {
            o << "nem elerheto" << endl;
        }
        else
        {
            print(s, i, parent);
            o << endl;
        }
    }
}

int main()
{
    int n, m, s;
    f >> n >> m >> s;

    vector<vp> graph(n);
    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        f >> a >> b >> w;
        graph[a].push_back(make_pair(b, w));
    }

    vector<int> dist, parent;
    dijkstra(s, graph, dist, parent);

    print_dist(s, dist, parent);

    return 0;
}
