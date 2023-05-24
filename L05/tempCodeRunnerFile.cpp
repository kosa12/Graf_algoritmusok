for (int i = 0; i < graph[node].size(); i++)
    {
        int nextNode = graph[node][i];
        findCriticalPath(graph, activities, path, nextNode);
    }