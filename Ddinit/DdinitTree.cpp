#include "DdinitTree.hpp"


DdinicTrees::DdinicTrees(std::vector<std::map<int, int>> a, int& floval, int s, int t){
    adj = a;
    int n = adj.size();
    source = s;
    sink = t;
    levels = std::vector<int>(n+1);
    upEdge = std::vector<std::map<int, int>>(n+1);
    nextEdge = std::vector<std::map<int, int>>(n+1);
    tree = new ST_Tree(false, n, 2);
    for ( int v = 1; v<n; v++){
        tree->update(v, 1000000);
        levels[v] = 0;
        upEdge[v] = std::map<int, int>();
        nextEdge[v] = std::map<int, int>();
    }

    while(newPhase()){
        while(findPath()){
            floval += augment();
        }
    }
}


bool DdinicTrees::findPath(){
    int u , v;
    std::map<int, int> e;
    while(nextEdge[source].begin() != nextEdge[source].end()){
        u = tree->root(source);
        e = nextEdge[u];
        while(true){
            if (u == sink){
                return true;
            }
            if (e.begin() == e.end()){
                nextEdge[u].clear();
                break;
            }
            v = e.begin()->first;
            if (tree->cost(u)>0 && levels[v] == levels[u] +1 && nextEdge[v].begin() != nextEdge[v].end()){
                upEdge[v][u] = e.begin()->second;
                nextEdge[u].erase(v);
                break;

            }
        }
    }



}