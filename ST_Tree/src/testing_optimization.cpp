#include <chrono>
#include "ST_Tree.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main()
{
    std::ofstream outFile("opt_test_dur0.txt");
    std::ofstream outFile2("opt_test_dur1.txt");
    std::vector<int> test_values = {10, 20, 40, 100, 200, 250, 350, 450, 500};
    for (int nodes : test_values)
    {
        ST_Tree ST = ST_Tree(false, nodes, 0);
        ST_Tree ST_opt = ST_Tree(true, nodes, 0);
        
        auto timeByDefStart = std::chrono::high_resolution_clock::now();
        for (int i = 1; i < nodes; i++)
            ST.link(i, i+1, 1);
        for (int i = 1; i < nodes; i++)
            ST.cut(i);
        auto timeByDefEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration1 = timeByDefEnd - timeByDefStart;
        
        auto timeByOptStart = std::chrono::high_resolution_clock::now();
        for (int i = 1; i < nodes; i++)
            ST_opt.link(i, i+1, 1);
        for (int i = 1; i < nodes; i++)
            ST_opt.cut(i);
        auto timeByOptEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration2 = timeByOptEnd - timeByOptStart;
        
        std::cout << "input size: " << nodes << std::endl;
        std::cout << "default time: " << duration1.count() << std::endl;
        std::cout << "optimized time: " << duration2.count() << std::endl;

        outFile << "x: " << nodes << ", y: " << duration1.count() << " seconds\n";
        outFile2 << "x: " << nodes << ", y: " << duration2.count() << " seconds\n";
    }
}