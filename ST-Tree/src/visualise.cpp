#include "visualise.hpp"

    // Function to generate and display the combined graph
void GraphManager::displayCombinedGraph(std::vector<std::vector<int>> bold_edges, std::vector<std::vector<int>> dashed_edges, std::string filename) {
    
    std::ofstream dot_file("combined_graph.dot");
    dot_file << "digraph G {\n";
    
    // Write bold edges
    for (const auto& edge : bold_edges) {
        dot_file << edge[0] << " -> " << edge[1] << " [style=bold";
        dot_file << ", label=" << edge[2]<< "];\n";
    }
    // boost::write_graphviz(dot_file, g);
    // boost::graph_traits<Graph>::edge_iterator ei, ei_end;
    // for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei) {
    //     dot_file << boost::source(*ei, g) << " -> " << boost::target(*ei, g) << ";\n";
    // }
    // dot_file << "}\n";

    for (const auto& edge : dashed_edges) {
        dot_file << edge[0] << " -> " << edge[1] << " [style=dashed";
        dot_file << ", label=" << edge[2]<< "];\n";
    }
    
    // Create vertices
    for (int i = 1; i <= vertices; i++)
        dot_file << i << "; \n";
    dot_file << "}\n";

    // Close the file
    dot_file.close();
    std::string command = "dot -Tpng combined_graph.dot -o " + filename + ".png";
    system(command.c_str());
    command = "open " + filename + ".png";
    system(command.c_str());
}


// int main() {
//     // Create an instance of the GraphManager
//     GraphManager graph_manager(7);

//     std::vector<std::pair<int, int>> bold_edges = {{0, 1}, {1, 2}, {2, 3}, {4, 5}, {5, 6}};
//     std::vector<std::pair<int, int>> dashed_edges = {{0, 4}};



//     // Generate and display the combined graph
//     graph_manager.displayCombinedGraph(bold_edges, dashed_edges);

//     return 0;
// }
