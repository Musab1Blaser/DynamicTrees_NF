#include "ST_Tree.hpp"

int main()
{
    // std::map<int, int> treePar = {{1, 2}, {2, 3}, {3, 4}, {5, 2}, {6, 4}};
    // ST_Tree ST = ST_Tree(treePar);
    ST_Tree ST = ST_Tree(6);
    ST.link(2, 1, 0);
    ST.link(6, 5, 0);
    ST.link(4, 2, 0);
    ST.link(5, 2, 0);
    ST.link(3, 1, 0);
    ST.cut(2);
}