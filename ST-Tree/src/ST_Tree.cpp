#include "ST_Tree.hpp"
#include <set>

ST_Tree::ST_Tree(std::map<int, int>& treePar)
{
    for (const auto &[u, v] : treePar)
    {
        vertices[u] = new ST_Node(true, u);
        dparent[u] = v; // remove - instead link trees/vertices
    }
}

ST_Node* ST_Tree::path(int v) {
    ST_Node* cur = vertices[v];
    while (cur->bparent)
        cur = cur->bparent;
    return cur;
}

int head(ST_Node* p)
{
    return (p->reversed) ? p->btail->vertex_id : p->bhead->vertex_id;
}

int tail(ST_Node* p)
{
    return (p->reversed) ? p->bhead->vertex_id : p->btail->vertex_id;
}