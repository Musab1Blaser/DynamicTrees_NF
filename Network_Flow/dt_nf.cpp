#include "dt_nf.hpp"

 

std::vector<std::map<int, int>> adj_inv(std::vector<std::map<int, int>> adj){
    int n = adj.size();
    std::vector<std::map<int, int>> inv(n);
    for(int v = 1; v < n; v++){
        for (const auto& [u, c]: adj[v]){
            inv[u][v] = c;
        }
    }
    return inv;
};

int dinicMaxFlow(int s, int t, 
std::vector<std::map<int, int>> adj) {
    int n = adj.size(); //the number of nodes
    GraphManager* g = new  GraphManager(n);
    ST_Tree* tree = new ST_Tree(false, n-1, 0);
    std::vector<std::map<int, int>> inv = adj_inv(adj);
    std::vector<std::map<int, int>> adj_copy = adj_inv(inv);
    while (true){
        int v = tree->root(s);
        if (v==t){
            v = tree->mincost(s);
            int c = tree->cost(v);
            tree->update(s, -c);
            g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
            while(tree->cost(v) == 0){
                v = tree->mincost(s);
                tree->cut(v);
                g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
            }
        }
        else if (adj[v].begin() == adj[v].end()){
            if (v==s){
                break;
            }
            else{
                for (const auto& [u, c]: inv[v]){
                    if (v == tree->parent(u)){
                        tree->cut(u);
                        g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
                    }
                    adj[u].erase(v);
                }
                inv[v].clear();
            }
        }
        else
        {
            int w;
            int c;
            for (const auto& [a, b] : adj_copy[v])
            {
                if (tree->root(a) != v)
                {
                    w = a;
                    c = b;
                    break;
                }
            }
            adj_copy[v].erase(w);
            tree->link(v, w, c);
            g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
        }
    }
    int flow = 0;
    for (int v = 0; v < n; v++){
        if (v!=t){
            if (t == tree->parent(v)){
                flow+=adj[t][v]-tree->cost(v);
            }
        }
    }
    return flow;
}


