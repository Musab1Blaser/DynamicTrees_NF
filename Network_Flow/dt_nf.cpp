#include "dt_nf.hpp"

void addRevEdges(std::vector<std::map<int, std::pair<int, int>>>& adj){
    int n = adj.size();
    // std::cout << n << std::endl;
    for (int v = 1; v < n; v++){
        for (const auto& [u, c]: adj[v]){
            // printf("%i %i\n", u, v);
            if (adj[u].count(v) == 0){
                adj[u][v] = {0, 0};
                // printf("%i %i\n", u, v);
            }
        }
    }
}


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

int sendFlow(int u, int flow, int t, std::vector<std::map<int, std::pair<int, int>>>& adj, std::vector<int>& level, std::vector<int>& start)
{
    // Sink reached
    if (u == t)
        return flow;
 
    // Traverse all adjacent edges one -by - one.
    for (; start[u] < adj[u].size(); start[u]++) {
        // Pick next edge from adjacency list of u
        std::pair<int, int>& e = adj[u][start[u]];
 
        if (level[start[u]] == level[u] + 1 && e.second < e.first) {
            // find minimum flow from u to t
            int curr_flow = std::min(flow, e.first - e.second);
 
            int temp_flow
                = sendFlow(start[u], curr_flow, t, adj, level, start);
 
            // flow is greater than zero
            if (temp_flow > 0) {
                // add flow  to current edge
                e.second += temp_flow;
 
                // subtract flow from reverse edge
                // of current edge
                adj[start[u]][u].second -= temp_flow;
                return temp_flow;
            }
        }
    }
 
    return 0;
}

int DinicMaxflow(int s, int t, std::vector<std::map<int, std::pair<int, int>>> adj)
{
    int n = adj.size(); //the number of nodes

    // Corner case
    if (s == t)
        return -1;
 
    int total = 0; // Initialize result
    std::vector<int> level (n);
 
    // Augment the flow while there is path
    // from source to sink
    while (BFS(s, t, adj, level) == true) {
        // store how many edges are visited
        // from V { 0 to V }
        std::vector<int> start (n, 0);
 
        // while flow is not zero in graph from S to D
        while (int flow = sendFlow(s, INT32_MAX, t, adj, level, start)) {
 
            // Add path flow to overall flow
            total += flow;
        }
    }
 
    // return maximum flow
    return total;
}

int blockingPaths(int s, int t, 
std::vector<std::map<int, std::pair<int, int>>>& adj,
std::vector<int>& start, std::vector<int>& level, bool optim, int debug) {
    int n = adj.size(); //the number of nodes
    GraphManager* g = new  GraphManager(n-1);
    ST_Tree* tree = new ST_Tree(optim, n-1, 0);
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
            while(tree->parent(s) != -1){
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
                    c = e.second.first - e.second.second;
                    break;
                }
            }

            if (w != -1)
            {
                tree->link(v, w, c);
                children[w].push_back(v);
                if (debug) g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
            }
            else
            {
                if (v==s){
                    for (int i = 1; i < n; i++)
                    {
                        int j = tree->parent(i);
                        if (j != -1)
                        {
                            int change = (adj[i][j].first - tree->cost(i)) - adj[i][j].second; // change in flow
                            adj[i][j].second += change;
                            adj[j][i].second -= change;
                            tree->cut(i);
                            if (debug) g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
                        }
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
                    children[v].clear();
                    if (debug) g->displayCombinedGraph(tree->getAllEdges(), tree->getAllDashEdges(), "flow", 0);
                }
            }
        } 
    }
    return flow;
}

int DinicMaxflowDT(int s, int t, std::vector<std::map<int, std::pair<int, int>>> adj, bool optim)
{

    int n = adj.size(); //the number of nodes
    addRevEdges(adj);
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
        std::vector<int> start (n, 0);
 
        // while flow is not zero in graph from S to D
        total += blockingPaths(s, t, adj, start, level, optim, 0);       
    }
 
    // return maximum flow
    return total;
}




    // for (int v = 1; v < n; v++){
    //     if (v!=t){
    //         if (t == tree->parent(v)){
    //             flow+=adj[t][v]-tree->cost(v);
    //         }
    //     }
    // }

