#include "ST_Tree.hpp"
#include <set>

ST_Tree::ST_Tree(std::map<int, int>& treePar)
{
    for (const auto &[u, v] : treePar)
    {
        dparent[u] = v;
        vertices[u] = new ST_Node(true);
    }
}