#include "visualise.hpp"
#include "ST_Tree.hpp"
#include <iostream>
#include <string>
#include <vector>


void displayGraph(GraphManager g, ST_Tree ST, std::string filename)
{
    std::vector<std::vector<int> > boldEdges = ST.getAllEdges(); // get all bold edges
    std::vector<std::vector<int> > dashedEdges = ST.getAllDashEdges(); // get all dashed edges
    g.displayCombinedGraph(boldEdges, dashedEdges, filename); // display the graph
}


int main()
{
    int nodes;
    std::cout << "How many nodes do you want in the Graph: ";
    std::cin >> nodes;

    ST_Tree ST = ST_Tree(nodes); // Initialise ST-Tree with 6 nodes numbered 1, 2, ..., 6
    GraphManager graph_manager(nodes);

    ST.link(2, 1, 4);
    ST.link(6, 5, 3);
    ST.link(4, 2, 6);
    ST.link(5, 2, 9);
    ST.link(3, 1, 5);
    ST.link(8,9,10);
    ST.mincost(5);
    ST.link(1,8,3);
    ST.evert(3);
    ST.update(8,2);
    ST.cut(2);
    ST.link(3,4,1);
    ST.link(7,6,3);
    ST.link(2,10,1);
    // ST.evert(6);
    // ST.evert(5);
    // ST.evert(4);
    // ST.evert(6);
    
    int op_num = 0;
    std::string opt {"_"};
    while (opt.size())
    {
        // List of Operations
        printf("\
Select the operation format you wish to use:\n\
1) parent v - returns the parent of v\n\
2) root v - return the root of the tree containing v\n\
3) cost v - return the cost of the edge (v, parent(v))\n\
4) mincost v - return the vertex w closest to root(v) with minimum edge cost on the path from v to root(v)\n\
5) update v x - Add x to all edges on the path from root(v) to v\n\
6) link a b w - Makes b parent of a with edge of weight w\n\
7) cut v - Divide the tree containing v into two trees by removing edge (v, parent(v))\n\
8) evert v - make v the root of the tree containing v\n");

        std::cin >> opt;
        // Tree Operations
        // Tree Queries
        if (opt == "parent")
        {
            int v;
            std::cin >> v;
            std::cout << "Result is: " << ST.parent(v) << std::endl;
        }
        else if (opt == "root")
        {
            int v;
            std::cin >> v;
            std::cout << "Result is: " << ST.root(v) << std::endl;
        }
        else if (opt == "cost")
        {
            int v;
            std::cin >> v;
            // std::cout << "Not implemented" << std::endl;
            std::cout << "Result is: " << ST.cost(v) << std::endl;
        }
        else if (opt == "mincost")
        {
            int v;
            std::cin >> v;
            // std::cout << "Not implemented" << std::endl;
            std::cout << "Result is: " << ST.mincost(v) << std::endl;
        }
        // Tree Operations
        else if (opt == "update")
        {
            int v, x;
            std::cin >> v >> x;
            // std::cout << "Not implemented" << std::endl;
            ST.update(v, x);
        }
        else if (opt == "link")
        {
            int a, b, w;
            std::cin >> a >> b >> w;
            ST.link(a, b, w);
        }
        else if (opt == "cut")
        {
            int v;
            std::cin >> v;
            ST.cut(v);
        }
        else if (opt == "evert")
        {
            int v;
            std::cin >> v;
            // std::cout << "Not implemented" << std::endl;
            ST.evert(v);
        }
        
        displayGraph(graph_manager, ST, "graph_results/"+std::to_string(++op_num)); // display the graph
    }
}