#pragma once

#include <map>

class ST_Tree
{
    private:
        struct ST_Node // Nodes - can represent vertices or edges. Their corresponding tree represents a path. Single Node trees represent trivial paths.
        {
            bool external;
            ST_Node* bparent;
            ST_Node(bool ext) : external{ext}, bparent{nullptr} {};

            bool reversed;
            int netmin;
            int netcost;
            ST_Node *bhead, *bleft, *bright, *btail;
            ST_Node (bool ext, ST_Node* par, bool rev, int netmi, int netcst) : external{ext}, bparent{par}, reversed{rev}, netmin{netmi}, netcost{netcst} {};
            ~ST_Node();  // To implement
        };
    
        ST_Tree(std::map<int, int>& treePar);    
        std::map<int, ST_Node*> vertices; 
        std::map<int, int> dparent;


        // DS elementary operations
        // Static Operations
        ST_Node* path(int v);  // To implement
        int head(ST_Node* p);  // To implement
        int tail(ST_Node* p);  // To implement

        int before(int v);  // To implement
        int after(int v);  // To implement

        int pcost(int v);  // To implement
        int pmincost(ST_Node* p);  // To implement
        
        void pupdate(ST_Node* p, double x);  // To implement
        void reverse(ST_Node* p);  // To implement

        // Dynamic Operations
        void construct(int v, int w, double x);  // To implement
        std::tuple<int, int, double> destroy (ST_Node* u);  // To implement
        
        void rotateleft(ST_Node* v);  // To implement
        void rotateright(ST_Node* v);  // To implement

        // concatenate + split


        ~ST_Tree(); // To implement

    // public:
};