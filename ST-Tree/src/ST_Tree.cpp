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
    ST_Node* u = new ST_Node(false, nullptr, false, 0, 0); // internal node, with no parent, not reversed, netmin and netcost 0
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
    std::tuple<ST_Node*, ST_Node*, double> result = {u->bleft, u->bright, 0};
    u->bleft->bparent = nullptr;
    u->bright->bparent = nullptr;
    delete u;
    return result;
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
        u->btail = u->bright->btail;

        v->bhead = v->bleft->bhead;
        v->btail = v->bright->btail;
    }
}

std::tuple<ST_Node*, ST_Node*, double, double> ST_Tree::split(int v)
{
    ST_Node* vNode = vertices[v];
    ST_Node *p {nullptr}, *q {nullptr};
    double x {-1}, y {-1};
    while (vNode->bparent)
    {
        ST_Node* cur = vNode->bparent;
        while (cur->bparent)
            rotate(cur);
        if (cur->bleft->btail == vNode)
            q = cur->bright, y = 0;
        else if (cur->bright->bhead == vNode)
            p = cur->bleft, x = 0;

        destroy(cur);
    }
    return {p, q, x, y};
}

ST_Node* ST_Tree::splice(ST_Node* p)
{
    int v = dparent[tail(p)];
    auto [q, r, x, y] = split(v);
    if (q) dparent[tail(q)] = v; // add cost adjustment
    p = concatenate(p, path(v), 0);
    if (r)
        return concatenate(p,r,0);
    else
        return p;
}

ST_Node* ST_Tree::expose(int v)
{
    auto [q, r, x, y] = split(v);
    if (q) dparent[tail(q)] = v; // add cost adjustment
    ST_Node* p;
    if (r)
        p = path(v);
    else
        p = concatenate(path(v), r, y);
        
    while (dparent[tail(p)] != -1)
        p = splice(p);

    return p;
}

// TODO - Check dparent implementation - where are dparents removed?
// TODO - link, cut and their dependencies
// TODO - visualise graph - menu modification system?
