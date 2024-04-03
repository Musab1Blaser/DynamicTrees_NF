#include "ST_Tree.hpp"
#include <set>

ST_Tree::ST_Tree(std::map<int, int>& treePar)
{
    for (const auto &[u, v] : treePar)
    {
        vertices[u] = new ST_Node(true, u);
        // dparent[u] = v; // remove - instead link trees/vertices
    }
}

ST_Node* ST_Tree::path(int v) {
    ST_Node* cur = vertices[v];
    while (cur->bparent)
        cur = cur->bparent;
    return cur;
}

int ST_Tree::head(ST_Node* p)
{
    return (p->reversed) ? p->btail->vertex_id : p->bhead->vertex_id;
}

int ST_Tree::tail(ST_Node* p)
{
    return (p->reversed) ? p->bhead->vertex_id : p->btail->vertex_id;
}

void ST_Tree::construct(ST_Node* v, ST_Node* w, double x) // v is to the left i.e. v is head of path -> lower in the actual tree
{
    ST_Node* u = new ST_Node(false, nullptr, false, 0, 0);
    u->bleft = v;
    v->bparent = u;
    u->bhead = v->bhead;
    u->bright = w;
    w->bparent = u; 
    u->btail = v->btail;
}

std::tuple<ST_Node*, ST_Node*, double> ST_Tree::destroy (ST_Node* u)
{
    dparent[u->bleft->btail->vertex_id] = u->bright->bhead->vertex_id;
    u->bleft->bparent = nullptr;
    u->bright->bparent = nullptr;
    delete u;
}

ST_Node* ST_Tree::concatenate(ST_Node* p, ST_Node* q, double x)
{
    construct(p, q, x);
    return p->bparent;
}

