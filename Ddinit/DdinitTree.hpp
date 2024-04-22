#pragma once
#include "../ST_Tree/src/ST_Tree.hpp"
#include "../ST_Tree/src/visualise.hpp"
#include <queue>
#include <vector>

class DdinicTrees{
    public: 
        DdinicTrees(std::vector<std::map<int, int>> a, int&, int, int);
    private:
        std::vector<std::map<int, int>> adj;
        std::vector<int> levels;
        std::vector<std::map<int, int>> upEdge;
        std::vector<std::map<int, int>> nextEdge;
        int source, sink;
        ST_Tree* tree;
        bool findPath();
        void augment();
        int newPhase();
};

