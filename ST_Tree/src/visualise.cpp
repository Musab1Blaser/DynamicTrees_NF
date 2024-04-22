#include "visualise.hpp"

    // Function to generate and display the combined graph
void GraphManager::displayCombinedGraph(std::vector<std::vector<int>> bold_edges, std::vector<std::vector<int>> dashed_edges, std::string filename, int mode) {
    
    std::ofstream dot_file("combined_graph.dot");
    dot_file << "digraph G {\n";
    
    // Write bold edges
    for (const auto& edge : bold_edges) {
        dot_file << edge[0] << " -> " << edge[1] << " [style=bold";
        dot_file << ", label=" << edge[2]<< "];\n";
    }

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
    if (mode == 2)
    {
        command = "open " + filename + ".png";
        system(command.c_str());
    }
}
