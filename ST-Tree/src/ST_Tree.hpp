#pragma once

#include <map>
struct ST_Node // Nodes - can represent vertices or edges. Their corresponding tree represents a path. Single Node trees represent trivial paths.
{
    bool external;
    int vertex_id;
    ST_Node* bparent;
    ST_Node(bool ext, int vert) : external{ext}, vertex_id{vert}, bparent{nullptr} {}; // External node/vertex constructor

    bool reversed;
    int netmin;
    int netcost;
    ST_Node *bhead, *bleft, *bright, *btail;
    // Internal node/edge constructor
    ST_Node (bool ext, ST_Node* par, bool rev, int netmi, int netcst) : external{ext}, bparent{par}, reversed{rev}, netmin{netmi}, netcost{netcst} {};
    // ~ST_Node();  // To implement
};

class ST_Tree
{
    // private:
    public:
        ST_Tree(std::map<int, int>& treePar);    
        
        std::map<int, ST_Node*> vertices; 
        std::map<int, int> dparent;
        std::map<int, int> dcost;


        // DS elementary operations
        // Static Operations
        ST_Node* path(int v);  
        int head(ST_Node* p);  
        int tail(ST_Node* p);  

        // int before(int v);  // To implement
        // int after(int v);  // To implement

        // int pcost(int v);  // To implement
        // int pmincost(ST_Node* p);  // To implement
        
        // void pupdate(ST_Node* p, double x);  // To implement
        // void reverse(ST_Node* p);  // To implement

        // Dynamic Operations
        void construct(ST_Node* v, ST_Node* w, double x);  
        std::tuple<ST_Node*, ST_Node*, double> destroy (ST_Node* u);  // To implement
        
        // void rotateleft(ST_Node* v);  // To implement
        // void rotateright(ST_Node* v);  // To implement

        // concatenate + split
        ST_Node* concatenate(ST_Node* p, ST_Node* q, double x);
        // std::tuple<ST_Node*, ST_Node*, double x, double y> split(int v);


        // ~ST_Tree(); // To implement

    // public:
};