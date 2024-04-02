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
            ~ST_Node();
        };
    
    public:
        ST_Tree(std::map<int, int>& treePar);    
        std::map<int, ST_Node*> vertices; 
        std::map<int, int> dparent;
        ~ST_Tree();
};