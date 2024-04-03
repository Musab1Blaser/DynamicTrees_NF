#include "ST_Tree.hpp"
#include <set>

ST_Tree::ST_Tree(std::map<int, int>& treePar)
{
    for (const auto &[u, v] : treePar)
    {
        if (!vertices.count(u))
            vertices[u] = new ST_Node(true, u);
        if (!vertices.count(v))
            vertices[v] = new ST_Node(true, v);
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
    u->btail = w->btail;
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

void ST_Tree::rotate(ST_Node* v)
{
    if (v->bparent)
    {
        ST_Node* u = v->bparent;
        if (u->bright == v) // rotate left
        {
            // give v's left child
            u->bright = v->bleft;
            u->bright->bparent = u;

            // update v's parent
            v->bparent = u->bparent;

            // make u left child
            v->bleft = u;
            u->bparent = v;

        }
        else
        {
            // give v's right child
            u->bleft = v->bright;
            u->bleft->bparent = u;

            // update v's parent
            v->bparent = u->bparent;
            
            // make u right child
            v->bright = u;
            u->bparent = v;


        }

        // update head and tail
        u->bhead = u->bleft->bhead;
        u->bhead = u->bright->btail;

        v->bhead = v->bleft->bhead;
        v->bhead = v->bright->btail;
    }
}

std::tuple<ST_Node*, ST_Node*, double, double> ST_Tree::split(int v)
{
    ST_Node* vNode = vertices[v];
    while (vNode->bparent)
    {
        ST_Node* cur = vNode->bparent;
        while (cur->bparent)
            rotate(cur);
        destroy(cur);
    }
}




