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


bool BFS(int s, int t, const std::vector<std::map<int, std::pair<int, int>>>& adj, std::vector<int>& level)
{
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




int DinicMaxflow(int s, int t, std::vector<std::map<int, std::pair<int, int>>> adj, bool optim)
{

    int n = adj.size(); //the number of nodes
    addRevEdges(adj);
    // GraphManager* g = new  GraphManager(n-1);
    // ST_Tree* tree = new ST_Tree(false, n-1, 0);
    // std::vector<std::map<int, std::pair<int, int>>> inv = adj_inv(adj);
    // Corner case
    if (s == t)
        return -1;
 
    int total = 0; // Initialize result
 
    // Augment the flow while there is path
    // from source to sink
    std::vector<int> level (n);
    while (BFS(s, t, adj, level) == true) {
        // store how many edges are visited
        // from V { 0 to V }
        std::vector<int> start (n+1, 0);
 
        // while flow is not zero in graph from S to D
        // while (int flow = sendFlow(s, INT_MAX, t, start)) {
 
        //     // Add path flow to overall flow
        //     total += flow;
        // }
        total += blockingPaths(s, t, adj, start, level, optim, 0);       
    }
 
    // return maximum flow
    return total;
}



int blockingPaths(int s, int t, 
std::vector<std::map<int, std::pair<int, int>>>& adj,
std::vector<int>& start, std::vector<int>& level, bool optim, int debug) {
    int n = adj.size(); //the number of nodes
    // addRevEdges(adj);
    GraphManager* g = new  GraphManager(n-1);
    ST_Tree* tree = new ST_Tree(optim, n-1, 5);
    // std::vector<std::map<int, std::pair<int, int>>> inv = adj_inv(adj);
    std::map<int, std::vector<int>> children;
    int flow = 0;

    while (true){
        int v = tree->root(s);
        if (v==t){
            v = tree->mincost(s);
            int c = tree->cost(v);
            tree->update(s, -c);
            flow += c;
            if (debug) g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
            while(true){
                v = tree->mincost(s);
                if (tree->cost(v) == 0)
                {
                    int change = adj[v][tree->parent(v)].first - adj[v][tree->parent(v)].second; // new flow
                    adj[v][tree->parent(v)].second += change;
                    adj[tree->parent(v)][v].second -= change;
                    tree->cut(v);
                    if (debug) g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
                }
                else
                    break;
                if (debug) g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
            }
        }
        else
        {
            int w = -1;
            int c = -1;
            while (start[v] < adj[v].size())
            {
                auto it = adj[v].begin();
                std::advance(it, start[v]++);
                std::pair<const int, std::pair<int, int>>& e = *it;
                if (level[e.first] == level[v]+1 && e.second.second < e.second.first)
                {
                    w = e.first;
                    c = e.second.first;
                    break;
                }
            }

            if (w != -1)
            {
                // adj[v].erase(w);
                // inv[w].erase(v);
                tree->link(v, w, c);
                children[w].push_back(v);
                if (debug) g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
            }
            else
            {
                if (v==s){
                    for (int i = 1; i < n; i++)
                        if (tree->parent(i) != -1)
                        {
                            int j = tree->parent(i);
                            int change = (adj[i][j].first - tree->cost(i)) - adj[i][j].second; // change in flow
                            adj[i][j].second += change;
                            adj[j][i].second -= change;
                            tree->cut(i);
                            if (debug) g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
                        }
                    break;
                }
                else
                {
                    for (int u : children[v])
                    {
                        int change = (adj[u][v].first - tree->cost(u)) - adj[u][v].second; // change in flow
                        adj[u][v].second += change;
                        adj[v][u].second -= change;
                        tree->cut(u);
                    }
                    if (debug) g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
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

