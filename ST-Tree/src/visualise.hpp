#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>
#include <vector>
#include <string>


// Define your graph types using Boost.Graph
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
// typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_color_t, boost::color_traits<boost::dashed_t>::color_type>> DashedGraph;



class GraphManager {
    private:
        int vertices;
    public:
    // Constructor
    GraphManager(int n):vertices(n) {};

    // Function to generate and display the combined graph
    void displayCombinedGraph(std::vector<std::vector<int>> bold_edges, std::vector<std::vector<int>> dashed_edges, std::string filename, int mode);
};