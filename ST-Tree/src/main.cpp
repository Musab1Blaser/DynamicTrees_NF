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
//     // tree to represent:
//     // std::map<int, int> treePar = {{2, 1}, {6, 5}, {4, 2}, {5, 2}, {3, 1}};

//     //       1
//     //     /   \
//     //    3     2
//     //        /   \
//     //       4     5
//     //              \
//     //               6
    ST_Tree ST = ST_Tree(6); // Initialise ST-Tree with 6 nodes numbered 1, 2, ..., 6
    GraphManager graph_manager(6);
    ST.link(2, 1, 0); // make 1 the parent of 2
    ST.link(6, 5, 0); // make 5 the parent of 6
    ST.link(4, 2, 0); // make 2 the parent of 4
    ST.link(5, 2, 0); // make 2 the parent of 5 - makes 2-4 connection dashed
    ST.link(3, 1, 0); // make 1 the parent of 3 - makes 1-2 connection dashed
    
    // can also directly initialise - gives slightly different output as links added in sorted order, instead of provided order
    // ST_Tree ST = ST_Tree(treePar, 6);
    // std::vector<std::vector<int> > g = ST.getAllGraphs(); 
    // for (auto &comp : g)
    // {
    //     for (auto &v : comp)
    //         std::cout << v << " ";
    //     std::cout << std::endl;
    // }
    displayGraph(graph_manager, ST, "graph1"); // display the graph
    int x;
    ST.cut(2); // break tree edge par(2)-2 -> result 1.3 and 4.2.5-6 (. signifies dashed edge) 
    // display the graph
    std::cin >> x;
    displayGraph(graph_manager, ST, "graph2");
}