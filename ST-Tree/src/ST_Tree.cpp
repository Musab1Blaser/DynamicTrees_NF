#include "ST_Tree.hpp"
#include <algorithm>
#include <fstream>
#include <queue>


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

// Getter for debugging
ST_Node* ST_Tree::get_vertex_ptr(int vertex_id)
{
    return vertices[vertex_id];
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
    u->bhead = vertices[head(v)];
    
    // Handle right node
    u->bright = w;
    w->bparent = u; 
    u->btail = vertices[tail(w)];

    // update costs
    // update netmin
    u->netmin = x;
    if (!u->bleft->external)
        u->netmin = std::min(u->netmin, u->bleft->netmin);
    if (!u->bright->external)
        u->netmin = std::min(u->netmin, u->bright->netmin);

    // update netcost
    u->netcost = x - u->netmin;

    // update children
    if (!u->bleft->external)
        u->bleft->netmin -= u->netmin; 
    if (!u->bright->external)
        u->bright->netmin -= u->netmin; 
}

std::tuple<ST_Node*, ST_Node*, double> ST_Tree::destroy (ST_Node* u) // Destroy the root of the tree, breaking it into two trees/represented paths -> return (path1, path2, edge1cost, edge2cost) - edge1, edge2 are the edges broken --  cost not handled
{
    // dparent[u->bleft->btail->vertex_id] = u->bright->bhead->vertex_id; - should not be modifying dashed paths inside helper functions
    std::tuple<ST_Node*, ST_Node*, double> result = {u->bleft, u->bright, 0};
    
    // Update costs of children
    if (!u->bleft->external)
        u->bleft->netmin += u->netmin;
    if (!u->bright->external)
        u->bright->netmin += u->netmin;

    if (u->reversed) // if the node I am destroying is reversed, then reverse both children
    {
        u->bright->reversed = !u->bright->reversed;
        u->bleft->reversed = !u->bleft->reversed;
    }

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
        if (v->reversed)
        {
            v->reversed = !v->reversed;
            ST_Node* tmp = v->bhead;
            v->bhead = v->btail;
            v->btail = tmp;
            
            tmp = v->bleft;
            v->bleft = v->bright;
            v->bright = tmp;

            if (!v->bleft->external) v->bleft->reversed = !v->bleft->reversed;
            if (!v->bright->external) v->bright->reversed = !v->bright->reversed;
        }

        
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

            // update costs
            double orig_v_nmin = v->netmin;
            // update v - right child
            if (!v->bright->external)
                v->bright->netmin += v->netmin;
            // update v - the child rotate up
            v->netcost += v->netmin;
            v->netmin = u->netmin;

            // update rotate parent
            u->netmin = u->netcost;
            if (!u->bleft->external)
                u->netmin = std::min(u->netmin, u->bleft->netmin);
            if (!u->bright->external)
                u->netmin = std::min(u->netmin, u->bright->netmin);
            u->netcost -= u->netmin;

            // update rotated parents children
            if (!u->bleft->external)
                u->bleft->netmin -= u->netmin;
            if (!u->bright->external)
                if (orig_v_nmin)
                    u->bright->netmin += orig_v_nmin;
                else
                    u->bright->netmin -= u->netmin;
            
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

            // update costs
            double orig_v_nmin = v->netmin;
            // update v - lef child
            if (!v->bleft->external)
                v->bleft->netmin += v->netmin;
            // update v - the child rotate up
            v->netcost += v->netmin;
            v->netmin = u->netmin;

            // update rotate parent
            u->netmin = u->netcost;
            if (!u->bleft->external)
                u->netmin = std::min(u->netmin, u->bleft->netmin);
            if (!u->bright->external)
                u->netmin = std::min(u->netmin, u->bright->netmin);
            u->netcost -= u->netmin;

            // update rotated parents children
            if (!u->bright->external)
                u->bright->netmin -= u->netmin;
            if (!u->bleft->external)
                if (orig_v_nmin)
                    u->bleft->netmin += orig_v_nmin;
                else
                    u->bleft->netmin -= u->netmin;
        }

        // update head and tail
        u->bhead = u->bleft->bhead;
        u->btail = u->bright->btail;

        v->bhead = v->bleft->bhead;
        v->btail = v->bright->btail;

        bool tmp = u->reversed;
        u->reversed = v->reversed;
        v->reversed = tmp;
    }
}

// Main operations
ST_Node* ST_Tree::concatenate(ST_Node* p, ST_Node* q, double x) // Connect two paths through an edge of cost x 
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
        bool cur_rev = get_reversal_state(cur);
        while (cur->bparent) // rotate edge to top to prepare for deletion
            rotate(cur); 

        // store whether left edge or right edge in path
        if ((!cur->reversed && tail(cur->bleft) == v) || (cur->reversed && head(cur->bright) == v)) // if i am in left, then the path being separated is from me to above - after(v) to tail(path)
            q = (cur->reversed) ? cur->bleft : cur->bright, y = cur->netcost + cur->netmin;
        else if ((!cur->reversed && head(cur->bright) == v) || (cur->reversed && tail(cur->bleft) == v)) // if i am in right, then the path being separated is from me to bottom - from head(path) to before(v)
            p = (cur->reversed) ? cur->bright : cur->bleft, x = cur->netcost + cur->netmin;

        destroy(cur); // delete edge
    }
    return {p, q, x, y};
}

// Path Partition functions - bold and dashed edges
ST_Node* ST_Tree::splice(ST_Node* p) // Extend current bold path upwards by converting one dashed edge  -- cost not handled
{
    int v = dparent[tail(p)]; // find node above me outside my path
    auto [q, r, x, y] = split(v); // r is path to root
    if (q) // q is other downward path
    {
        dparent[tail(q)] = v; // make it dashed
        dcost[tail(q)] = x;
    }

    dparent[tail(p)] = -1; // dashed edge removed
    p = concatenate(p, path(v), dcost[tail(p)]); // connect me to the node above me
    if (r) // if more nodes on way to root
        return concatenate(p, r, y); // connect me to the path above v
    else // no path to root
        return p;
}

ST_Node* ST_Tree::expose(int v) // Create bold path from this node to root of tree -- cost not handled
{
    auto [q, r, x, y] = split(v); // cut me off from anything below
    if (q) // if path afer me
    {
        dparent[tail(q)] = v; // then make me its dashed parent
        dcost[tail(q)] = x;
    }
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

bool ST_Tree::get_reversal_state(ST_Node* v)
{
    bool rev = v->reversed;
    while (v->bparent)
    {
        v = v->bparent;
        rev = rev ^ v->reversed;
    }
    return rev;
}

int ST_Tree::before(int v) { // returns the vertex before v on path(v), if v is the tail return null -- reversed not considered
    ST_Node* u = vertices[v];

    // deepest node that is the right child of its parent
    ST_Node* deepest_right = nullptr;
    ST_Node* current = u;
    bool rev = false;
    if (current->bparent)
    {
        rev = get_reversal_state(current);
        while (current->bparent) 
        {
            rev ^= current->reversed;
            if ((current->bparent->bright == current) ^ rev) {  
                deepest_right = current->bparent;
                break;
            }
            current = current->bparent;
        }
    }

    // rightmost external descendant of left sibling
    if (deepest_right) {
        if (rev)
            return head(deepest_right->bright); 
        else
            return tail(deepest_right->bleft);
    }

    return -1;
}

int ST_Tree::after(int v) { // returns the vertex after v on path(v), if v is the head return null
    ST_Node* u = vertices[v];

    // deepest node that is the left child of its parent
    ST_Node* deepest_left = nullptr;
    ST_Node* current = u;
    bool rev = false;
    if (current->bparent)
    {
        rev = get_reversal_state(current);
        while (current->bparent) {
            rev ^= current->reversed;
            if ((current->bparent->bleft == current) ^ rev) {  
                deepest_left = current->bparent;
                break;
            }
            current = current->bparent;
        }
    }

    // leftmost external descendant of right sibling
    if (deepest_left) {
        if (rev)
            return tail(deepest_left->bleft); 
        else
            return head(deepest_left->bright);
    }

    return -1;
}

int ST_Tree::parent(int v){
    if (tail(path(v)) == v){ //so no parent or dashed parent
        return dparent[v];
    }

    return after(v);
}

int ST_Tree::root(int v){
    return tail(expose(v));
}

// TODO - visualise graph - menu modification system?
std::vector<ST_Node*> ST_Tree::getAllUniquePaths(){
    std::map <ST_Node*, int> paths;
    for ( int i = vertices.size(); i > 0; i--){
        ST_Node* p = path(i);
        if (paths.find(p) == paths.end())
            paths[p] = 1;
    };
    std::vector<ST_Node*> uniquePaths;
    for (auto const& [key, val] : paths)
        uniquePaths.push_back(key);
    return uniquePaths;
}

std::vector<std::vector<int>> ST_Tree::getAllGraphs(){
    std::vector<std::vector<int>> graphs;
    std::vector<ST_Node*> paths = getAllUniquePaths();
    for (ST_Node* p : paths){
        std::vector<int> graph;
        int cur_val = head(p);
        while (cur_val != tail(p))
        {
            graph.push_back(cur_val);
            cur_val = after(cur_val);
        }
        graph.push_back(cur_val);
        std::reverse(graph.begin(), graph.end());
        graphs.push_back(graph);
    }
    return graphs;
}

std::vector<std::vector<int>> ST_Tree::getAllEdges(){
    std::vector<std::vector<int>> edges;
    std::vector<std::vector<int>> graphs = getAllGraphs();
    std::cout << "Internal Paths:\n";
    for (std::vector<int> graph : graphs){
        std::cout << graph[0];
        for (int i = 0; i < graph.size() - 1; i++){
            std::cout << " " << graph[i+1];
            std::vector<int> edge = {graph[i], graph[i+1], (int) cost(graph[i+1])};
            edges.push_back(edge);
        }
        std::cout << std::endl;
    }
    return edges;
};

std::vector<std::vector<int>> ST_Tree::getAllDashEdges(){
    std::vector<std::vector<int>> edges;
    for (const auto &[u, v] : dparent){
        if (v!=-1){
            std::vector<int> edge = {v, u, (int) dcost[u]};
            edges.push_back(edge);
        }
    }
    return edges;
};


int ST_Tree::grosscost(ST_Node* v){
    return ((v->netcost) + (grossmin(v)));
}

int ST_Tree::grossmin(ST_Node* v){
  int min_value = v->netmin;

  // traverse upwards till root
  while (v->bparent != nullptr) {
        v = v->bparent;
        min_value += v->netmin;
  }

  return min_value;
}

double ST_Tree::pcost(int v){
    ST_Node* u = vertices[v];

    // deepest node that is the left child of its parent
    ST_Node* deepest_left = nullptr;
    ST_Node* current = u;
    bool rev = get_reversal_state(current->bparent);
    while (current->bparent) {
        if (!rev){
            if (current->bparent->bleft == current) {  
            deepest_left = current;
            break;
            }
        current = current->bparent;
        rev ^= current->reversed;
        }
        else{
            if (current->bparent->bright == current) {  
            deepest_left = current;
            break;
            }
        current = current->bparent;
        rev ^= current->reversed;
        }

    }

    return grosscost(deepest_left->bparent);
}

double ST_Tree::pmincost(ST_Node* p){
    ST_Node* u = p;

    bool rev = get_reversal_state(u);
    while (u->netcost !=0 and (u->bright->external or u->bright->netmin >=0)){
        if (!rev){
            if (!u->bright->external and u->bright->netcost==0){
            u = u->bright;
            }
            else if (u->netcost > 0){
                u = u->bleft;
            }
            rev ^= u->reversed;
        }
        else{
            if (!u->bleft->external and u->bleft->netcost==0){
            u = u->bleft;
            }
            else if (u->netcost > 0){
                u = u->bright;
            }
            rev ^= u->reversed;
        }
    }

    return u->bleft->btail->vertex_id;
}

void ST_Tree::pupdate(ST_Node* p, double x){
    p->netmin = p->netmin + x;
}

void ST_Tree::reverse(ST_Node* p){
    p->reversed = !p->reversed;
}

double ST_Tree::cost(int v){
    if (v==tail(path(v))){
        return dcost[v];
    }
    else{
        return pcost(v);
    }
}

double ST_Tree::mincost(int v){
    return pmincost(expose(v));
}

void ST_Tree::update(int v, double x){
    return pupdate(expose(v), x);
}

void ST_Tree::evert(int v){
    reverse(expose(v));
    dparent[v] = -1;
}

std::pair<int, int> ST_Tree::getEdge(ST_Node* eNode)
{
    if (eNode->reversed)
        return {head(eNode->bright), tail(eNode->bleft)};
    else
        return {tail(eNode->bleft), head(eNode->bright)};
}

void ST_Tree::displayInternalGraph() {
    std::vector<ST_Node*> path_list = getAllUniquePaths(); 
    std::ofstream dot_file("internal_graph.dot");
    dot_file << "digraph G {\n";
    
    // Add Connections for each path
    for (ST_Node* p : path_list)
    {
        std::queue<ST_Node*> bfs;
        bfs.push(p);
        while (bfs.size())
        {
            ST_Node* cur = bfs.front();
            bfs.pop();
            if (!cur->external)
            {
                std::pair<int, int> edgeName = getEdge(cur);
                dot_file << "\"(" << edgeName.first << "," << edgeName.second <<  ((cur->reversed) ? ")*" : ")") << "\" [shape=box];\n"; // create internal node shape
                // left child connection
                if (cur->bleft->external) // if external
                {
                    dot_file << cur->bleft->vertex_id << " [shape=circle];\n";
                    dot_file << "\"(" << edgeName.first << "," << edgeName.second <<  ((cur->reversed) ? ")*" : ")") << "\" -> " << cur->bleft->vertex_id << ";\n";
                }
                else // if internal
                {
                    std::pair<int, int> childEdgeName = getEdge(cur->bleft);
                    dot_file << "\"(" << edgeName.first << "," << edgeName.second <<  ((cur->reversed) ? ")*" : ")") << "\" -> " << "\"(" << childEdgeName.first << "," << childEdgeName.second <<  ((cur->bleft->reversed) ? ")*" : ")") << "\";\n";
                    bfs.push(cur->bleft);                    
                }

                // right child connection
                if (cur->bright->external) // if external
                {
                    dot_file << cur->bright->vertex_id << " [shape=circle];\n";
                    dot_file << "\"(" << edgeName.first << "," << edgeName.second <<  ((cur->reversed) ? ")*" : ")") << "\" -> " << cur->bright->vertex_id << ";\n";
                }
                else // if internal
                {
                    std::pair<int, int> childEdgeName = getEdge(cur->bright);
                    dot_file << "\"(" << edgeName.first << "," << edgeName.second <<  ((cur->reversed) ? ")*" : ")") << "\" -> " << "\"(" << childEdgeName.first << "," << childEdgeName.second <<  ((cur->bright->reversed) ? ")*" : ")") << "\";\n";
                    bfs.push(cur->bright);                    
                }
                
                // head and tail
                dot_file << "\"(" << edgeName.first << "," << edgeName.second <<  ((cur->reversed) ? ")*" : ")") << "\" -> " << cur->bhead->vertex_id << " [style=dashed, label = h];\n";
                dot_file << "\"(" << edgeName.first << "," << edgeName.second <<  ((cur->reversed) ? ")*" : ")") << "\" -> " << cur->btail->vertex_id << " [style=dashed, label = t];\n";
            }


        }
    }

    
    dot_file << "}\n";

    // Close the file
    dot_file.close();
    std::string command = "dot -Tpng internal_graph.dot -o internal_graphs.png";
    system(command.c_str());
    command = "open internal_graphs.png";
    system(command.c_str());
}