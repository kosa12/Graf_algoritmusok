// Kosa Matyas, 512

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream f("3_be.txt");
ofstream o("3_ki.txt");

struct Activity
{
    int duration;
    int earliest_start;
    int earliest_finish;
    int latest_start;
    int latest_finish;
};

void findCriticalPath(vector<vector<int>> &graph, vector<int> &indegree, vector<Activity> &activities)
{
    int n = graph.size();
    vector<int> earliest_time(n, 0);
    vector<int> latest_time(n, 0);
    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : graph[u])
        {
            indegree[v]--;
            if (indegree[v] == 0)
            {
                q.push(v);
            }
            earliest_time[v] = max(earliest_time[v], earliest_time[u] + activities[u].duration);
        }
    }

    latest_time[n - 1] = earliest_time[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        for (int v : graph[i])
        {
            latest_time[i] = (latest_time[i] == 0) ? latest_time[v] - activities[i].duration : min(latest_time[i], latest_time[v] - activities[i].duration);
        }
    }

    for (int i = 0; i < n; i++)
    {
        activities[i].earliest_start = earliest_time[i];
        activities[i].earliest_finish = earliest_time[i] + activities[i].duration;
        activities[i].latest_start = latest_time[i] - activities[i].duration;
        activities[i].latest_finish = latest_time[i];
    }

    cout << "Critical path: 1 ";
    for (int i = 0; i < n; i++)
    {
        if (earliest_time[i] == latest_time[i])
        {
            cout << i + 1 << " ";
        }
    }
    cout << endl;

    cout << "Activities:" << endl;
    for (int u = 0; u < n; u++)
    {
        for (int v : graph[u])
        {
            if (earliest_time[u] + activities[u].duration == earliest_time[v])
            {
                cout << u + 1 << " -> " << v + 1 << ": duration=" << activities[u].duration << ", earliest_start=" << activities[u].earliest_start << ", earliest_finish=" << activities[u].earliest_finish << ", latest_start=" << activities[u].latest_start << ", latest_finish=" << activities[u].latest_finish << endl;
            }
        }
    }
}

int main()
{
    int n;
    f >> n;

    vector<int> duration(n);
    for (int i = 0; i < n; i++)
    {
        f >> duration[i];
    }

    vector<vector<int>> graph(n);
    vector<int> indegree(n, 0);
    for (int i = 0; i < n; i++)
    {
        int u, v;
        f >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        indegree[v]++;
    }

    vector<Activity> activities(n);
    for (int i = 0; i < n; i++)
    {
        activities[i].duration = duration[i];
    }

    findCriticalPath(graph, indegree, activities);

    return 0;
}