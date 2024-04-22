#include "dt_nf.hpp"

void addRevEdges(std::vector<std::map<int, std::pair<int, int>>>& adj){
    int n = adj.size();
    for (int v = 1; v < n; v++){
        for (const auto& [u, c]: adj[v]){
            if (adj[u].count(v) == 0){
                adj[u][v] = {0, 0};
            }
        }
    }
}

std::vector<std::map<int, std::pair<int, int>>> adj_inv(const std::vector<std::map<int, std::pair<int, int>>>& adj){
    int n = adj.size();
    std::vector<std::map<int, std::pair<int, int>>> inv(n);
    for(int v = 1; v < n; v++){
        for (const auto& [u, c]: adj[v]){
            inv[u][v] = c;
        }
    }
    return inv;
};


bool BFS(int s, int t, const std::vector<std::map<int, std::pair<int, int>>>& adj)
{
    std::vector<int> level;
    for (int i = 1; i < adj.size(); i++)
        level[i] = -1;
 
    level[s] = 0; // Level of source vertex
 
    // Create a queue, enqueue source vertex
    // and mark source vertex as visited here
    // level[] array works as visited array also.
    std::list<int> q;
    q.push_back(s);
    

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (auto [v, c] : adj[u]) {
            if (level[v] < 0 && c.second < c.first) {
                // Level of current vertex is,
                // level of parent + 1
                level[v] = level[u] + 1;
                q.push_back(v);
            }
        }
    }
 
    // IF we can not reach to the sink we
    // return false else true
    return level[t] < 0 ? false : true;
}




int DinicMaxflow(int s, int t, std::vector<std::map<int, std::pair<int, int>>> adj)
{

    int n = adj.size(); //the number of nodes
    addRevEdges(adj);
    GraphManager* g = new  GraphManager(n-1);
    ST_Tree* tree = new ST_Tree(false, n-1, 0);
    std::vector<std::map<int, std::pair<int, int>>> inv = adj_inv(adj);
    // Corner case
    if (s == t)
        return -1;
 
    int total = 0; // Initialize result
 
    // Augment the flow while there is path
    // from source to sink
    while (BFS(s, t, adj) == true) {
        // store how many edges are visited
        // from V { 0 to V }
        int* start = new int[n + 1]{ 0 };
 
        // while flow is not zero in graph from S to D
        while (int flow = sendFlow(s, INT_MAX, t, start)) {
 
            // Add path flow to overall flow
            total += flow;
        }
       
          // Remove allocated array
          delete[] start;
    }
 
    // return maximum flow
    return total;
}



int dinicMaxFlow(int s, int t, 
std::vector<std::map<int, std::pair<int, int>>> adj) {
    int n = adj.size(); //the number of nodes
    addRevEdges(adj);
    GraphManager* g = new  GraphManager(n-1);
    ST_Tree* tree = new ST_Tree(false, n-1, 0);
    std::vector<std::map<int, std::pair<int, int>>> inv = adj_inv(adj);
    int flow = 0;

    while (true){
        int v = tree->root(s);
        if (v==t){
            v = tree->mincost(s);
            int c = tree->cost(v);
            tree->update(s, -c);
            flow += c;
            g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
            while(true){
                v = tree->mincost(s);
                if (tree->cost(v) == 0)
                    tree->cut(v);
                else
                    break;
                g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
            }
        }
        else
        {
            int w = -1;
            int c = -1;
            int f = -1;
            for (const auto& [a, b] : adj[v])
            {
                if (tree->root(a) != v)
                {
                    w = a;
                    c = b.first;
                    f = b.second;
                    break;
                }
            }

            if (w != -1)
            {
                adj[v].erase(w);
                // inv[w].erase(v);
                tree->link(v, w, c);
                g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
            }
            else
            {
                if (v==s){
                    break;
                }
                else
                {
                    for (const auto& [u, c]: inv[v]){
                        if (v == tree->parent(u)){
                            tree->cut(u);
                            g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
                        }
                        if (adj[u].count(v)) adj[u].erase(v);
                    }
                    inv[v].clear();
                }
            }
        } 
    }
    return flow;
}
    // for (int v = 1; v < n; v++){
    //     if (v!=t){
    //         if (t == tree->parent(v)){
    //             flow+=adj[t][v]-tree->cost(v);
    //         }
    //     }
    // }

