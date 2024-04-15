#pragma once

#include <map>
#include <iostream>
struct ST_Node // Nodes of underlying tree - can represent vertices or edges of original tree. Their subtree represents a path in original tree. Single Node trees represent trivial/single node paths of original tree.
{
    bool external; // true/false
    int vertex_id; // vertex number
    ST_Node* bparent;
    ST_Node *bleft, *bright;
    ST_Node *bhead, *btail; // bottom-most and top-most nodes in path 
    
    // External node/vertex constructor
    ST_Node(bool ext, int vert) : external{ext}, vertex_id{vert}, bparent{nullptr}, bhead{this}, bleft{this}, bright{this}, btail{this} {}; 

    // not properly handled attributes:
    bool reversed;
    int netmin;
    int netcost;

    // Internal node/edge constructor
    ST_Node (bool ext, ST_Node* par, bool rev, int netmi, int netcst) : external{ext}, vertex_id{-1}, bparent{par}, reversed{rev}, netmin{netmi}, netcost{netcst} {};
};

class ST_Tree
{
    private:
        std::map<int, ST_Node*> vertices; // A map from vertex number to its corresponding node in path tree
        std::map<int, int> dparent; // dashed edges/parents map
        std::map<int, int> dcost; // cost of dashed edge  --  not handled


        // Elementary Path operations
        // Static Operations
        ST_Node* path(int v);  // Return the node representing the path v belongs to
        int head(ST_Node* p);  // Return head/lower-most node of path
        int tail(ST_Node* p);  // Return tail/upper-most node of path

        int before(int v);  // return the vertex right before v in the path, unless it is tail in which case return -1
        // int after(int v);  // return the vertex right after v in the path, unless it is head in which case return -1

        // int pcost(int v);  // To implement
        // int pmincost(ST_Node* p);  // To implement
        
        // void pupdate(ST_Node* p, double x);  // To implement
        // void reverse(ST_Node* p);  // To implement

        // Dynamic Operations
        // Suboperations
        void construct(ST_Node* v, ST_Node* w, double x);  // Create a new node corresponding to an edge connecting the two paths represented by v and w  --  cost not handled
        std::tuple<ST_Node*, ST_Node*, double> destroy (ST_Node* u);  // Destroy the root of the tree, breaking it into two trees/represented paths --  cost not handled
        
        void rotate(ST_Node* v); // rotate a node (representing an edge) upwards

        // possibly unnecessary:
        // void rotateleft(ST_Node* v);  // To implement
        // void rotateright(ST_Node* v);  // To implement

        // Main operations
        ST_Node* concatenate(ST_Node* p, ST_Node* q, double x); // Connect two paths through an edge of cost x  -- cost not handled
        std::tuple<ST_Node*, ST_Node*, double, double> split(int v); // Break a path at a node into path before and path after. Selected node becomes a trivial/single node path -- cost not handled

        // Path Partition functions - bold and dashed edges
        ST_Node* splice(ST_Node* p); // Extend current bold path upwards by converting one dashed edge  -- cost not handled
        ST_Node* expose(int v); // Create bold path from this node to root of tree -- cost not handled


    public:
        int after(int v);  // return the vertex right after v in the path, unless it is head in which case return -1
        // Constructors and Destructor
        ST_Tree(std::map<int, int>& treePar, int n);  // Construct based on input tree/forest and number of nodes (named 1 to n)
        ST_Tree(int n); // Create tree of n unconnected nodes (named 1 to n)
        // ~ST_Tree(); // To implement

        // Dynamic Tree Operations
        // int parent(int v); // To implement
        // int root(int v); // To implement

        // double cost(int v); // To implement
        // double mincost(int v); // To implement
        // void update(int v, double x); // To implement

        void link(int v, int w, double x); // Let v be a root of a tree. Connect w to v, effectively joining two trees  --  cost not handled
        double cut(int v); // Divide the tree into two by breaking at vertex v  -- cost not handled

        // void evert(int v); // To implement

};