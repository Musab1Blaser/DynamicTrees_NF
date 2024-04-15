#include "ST_Tree.hpp"
#include <set>

// Constructors
ST_Tree::ST_Tree(std::map<int, int>& treePar, int n) // Construct based on input tree/forest and number of nodes (named 1 to n)
{
    for (int i = 1; i <= n; i++)
    {
        vertices[i] = new ST_Node(true, i);
        dparent[i] = -1;
    }

    for (const auto &[u, v] : treePar)
    {
        link(u, v, 0);
    }
}

ST_Tree::ST_Tree(int n) // Create tree of n unconnected nodes (named 1 to n)
{ 
    for (int i = 1; i <= n; i++)
        vertices[i] = new ST_Node(true, i), dparent[i] = -1;
}

// Elemntary Path operations
// Static Operations
ST_Node* ST_Tree::path(int v) // Return the node representing the path v belongs to
{
    ST_Node* cur = vertices[v];
    while (cur->bparent) 
        cur = cur->bparent;
    return cur;
}

int ST_Tree::head(ST_Node* p) // Return head/lower-most node of path
{
    return (p->reversed) ? p->btail->vertex_id : p->bhead->vertex_id;
}

int ST_Tree::tail(ST_Node* p) // Return tail/upper-most node of path
{
    return (p->reversed) ? p->bhead->vertex_id : p->btail->vertex_id;
}

// Dynamic Operations
// Suboperations
void ST_Tree::construct(ST_Node* v, ST_Node* w, double x) // Create a new node corresponding to an edge connecting the two paths represented by v and w  --  cost not handled
{
    ST_Node* u = new ST_Node(false, nullptr, false, 0, 0); // internal node, with no parent, not reversed, netmin and netcost 0
    
    // Handle left node
    u->bleft = v;
    v->bparent = u;
    u->bhead = v->bhead;
    
    // Handle right node
    u->bright = w;
    w->bparent = u; 
    u->btail = w->btail;
}

std::tuple<ST_Node*, ST_Node*, double> ST_Tree::destroy (ST_Node* u) // Destroy the root of the tree, breaking it into two trees/represented paths -> return (path1, path2, edge1cost, edge2cost) - edge1, edge2 are the edges broken --  cost not handled
{
    dparent[u->bleft->btail->vertex_id] = u->bright->bhead->vertex_id;
    std::tuple<ST_Node*, ST_Node*, double> result = {u->bleft, u->bright, 0};
    
    // remove references to u and delete u
    u->bleft->bparent = nullptr;
    u->bright->bparent = nullptr;
    delete u;

    return result;
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

// Main operations
ST_Node* ST_Tree::concatenate(ST_Node* p, ST_Node* q, double x) // Connect two paths through an edge of cost x  -- cost not handled
{
    construct(p, q, x);
    return p->bparent;
}


std::tuple<ST_Node*, ST_Node*, double, double> ST_Tree::split(int v) // Break a path at a node into path before and path after. Selected node becomes a trivial/single node path -- cost not handled
{
    ST_Node* vNode = vertices[v];
    ST_Node *p {nullptr}, *q {nullptr};
    double x {-1}, y {-1};
    while (vNode->bparent) // while there are edges connected to me in the path
    {
        ST_Node* cur = vNode->bparent; // Find an edge connected to me
        while (cur->bparent) // rotate edge to top to prepare for deletion
            rotate(cur); 

        // store whether left edge or right edge in path
        if (cur->bleft->btail == vNode)
            q = cur->bright, y = 0;
        else if (cur->bright->bhead == vNode)
            p = cur->bleft, x = 0;

        destroy(cur); // delete edge
    }
    return {p, q, x, y};
}

// Path Partition functions - bold and dashed edges
ST_Node* ST_Tree::splice(ST_Node* p) // Extend current bold path upwards by converting one dashed edge  -- cost not handled
{
    int v = dparent[tail(p)]; // find node above me outside my path
    auto [q, r, x, y] = split(v); // r is path to root
    if (q) dparent[tail(q)] = v; // q is other downward path - make it dashed
    
    p = concatenate(p, path(v), 0); // connect me to the node above me
    if (r) // if more nodes on way to root
        return concatenate(p,r,0); // connect me to the path to root
    else // no path to root
        return p;
}

ST_Node* ST_Tree::expose(int v) // Create bold path from this node to root of tree -- cost not handled
{
    auto [q, r, x, y] = split(v); // cut me off from anything below
    if (q) dparent[tail(q)] = v; 

    // connect me upwards
    ST_Node* p; 
    if (r)
        p = concatenate(path(v), r, y);
    else
        p = path(v);
        
    // if not connected to root then keep connecting upwards
    while (dparent[tail(p)] != -1)
        p = splice(p);

    return p;
}


// Dynamic Tree Operations
void ST_Tree::link(int v, int w, double x) // Let v be a root of a tree. Connect w to v, effectively joining two trees  --  cost not handled
{
    concatenate(path(v), expose(w), x); // makes path from root of v to w bold
}

double ST_Tree::cut(int v) // Divide the tree into two by breaking at vertex v  -- cost not handled
{
    expose(v); // make path from me to root bold and everything below dashed
    auto [p, q, x, y] = split(v);
    dparent[v] = -1; // don't connect me to what I split off from
    return y;
}

int ST_Tree::before(int v) { // returns the vertex before v on path(v), if v is the tail return null
    ST_Node* u = vertices[v];

    //ST_Node* current = u;
    // while (current->bparent) {
    //     if (current->bparent->reversed)
    //         current->reversed = !current->reversed;
    //     current = current->bparent;
    // }

    // deepest node that is the right child of its parent
    ST_Node* deepest_right = nullptr;
    ST_Node* current = u;
    while (current->bparent) {
        if (current->bparent->bright == current) {  
            deepest_right = current->bparent;
            break;
        }
        current = current->bparent;
    }

    // rightmost external descendant 
    if (deepest_right) {
        return deepest_right->bleft->btail->vertex_id;
    }

    return -1;
}

// TODO - visualise graph - menu modification system?