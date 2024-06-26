
#include "ffnf.hpp"


int fordFulkerson(std::vector<std::map<int, std::pair<int, int>>> graph, int source, int sink) {
    unordered_map<int, int> parent;
    for (int i = 1; i < (int) graph.size(); i++){
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
                if (visited.count(node) || cost.first <= 0) {
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
            pathFlow = min(pathFlow, graph[parent[v]][v].first);
            v = parent[v];
        }
        maxFlow += pathFlow;
        v = sink;
        while (v != source) {
            int u = parent[v];
            if (graph[u].count(v)) {
                graph[u][v].first -= pathFlow;
            } else {
                graph[u][v].first = -pathFlow;
            }
            if (graph[v].count(u)) {
                graph[v][u].first += pathFlow;
            } else {
                graph[v][u].first = pathFlow;
            }
            v = parent[v];
        }
    }

    return maxFlow;
}