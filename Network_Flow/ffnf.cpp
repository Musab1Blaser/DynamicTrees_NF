
#include "ffnf.hpp"


int fordFulkerson(vector<map<int, int> >& graph, int source, int sink) {
    unordered_map<int, int> parent;
    for (int i = 1; i < graph.size() + 1; i++){
        parent[i] = -1;
    }
    int maxFlow = 0;

    auto bfs = [&](int start, int end) {
        queue<int> q;
        q.push(start);
        unordered_set<int> visited = {start};
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto& [node, cost] : graph[u]) {
                if (visited.count(node) || cost <= 0) {
                    continue;
                }
                visited.insert(node);
                q.push(node);
                parent[node] = u;
                if (node == end) {
                    return true;
                }
            }
        }
        return false;
    };

    while (bfs(source, sink)) {
        int pathFlow = 1000000000;
        int v = sink;
        while (v != source) {
            pathFlow = min(pathFlow, graph[parent[v]][v]);
            v = parent[v];
        }
        maxFlow += pathFlow;
        v = sink;
        while (v != source) {
            int u = parent[v];
            if (graph[u].count(v)) {
                graph[u][v] -= pathFlow;
            } else {
                graph[u][v] = -pathFlow;
            }
            if (graph[v].count(u)) {
                graph[v][u] += pathFlow;
            } else {
                graph[v][u] = pathFlow;
            }
            v = parent[v];
        }
    }

    return maxFlow;
}