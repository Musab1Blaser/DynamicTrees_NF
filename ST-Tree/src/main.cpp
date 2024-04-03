#include "ST_Tree.hpp"

int main()
{
    std::map<int, int> treePar = {{1, 2}, {2, 3}, {4, 2}};
    ST_Tree ST = ST_Tree(treePar);
    ST.concatenate(ST.path(1), ST.path(2), 0);
    ST.concatenate(ST.path(2), ST.path(3), 0);
    ST.concatenate(ST.path(4), ST.path(2), 0);
}