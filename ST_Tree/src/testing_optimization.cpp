#include <chrono>
#include "ST_Tree.hpp"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<int> test_values = {10, 100, 1000, 10000};
    for (int nodes : test_values)
    {
        ST_Tree ST = ST_Tree(false, nodes, 0);
        ST_Tree ST_opt = ST_Tree(true, nodes, 0);
        
        auto timeByDefStart = std::chrono::high_resolution_clock::now();
        for (int i = 1; i < nodes; i++)
            ST.link(i, i+1, 2);
        for (int i = 1; i < nodes; i++)
            ST.cut(i);
        auto timeByDefEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration1 = timeByDefEnd - timeByDefStart;
        
        auto timeByOptStart = std::chrono::high_resolution_clock::now();
        for (int i = 1; i < nodes; i++)
            ST_opt.link(i, i+1, 2);
        for (int i = 1; i < nodes; i++)
            ST_opt.cut(i);
        auto timeByOptEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration2 = timeByOptEnd - timeByOptStart;
        
        std::cout << "input size: " << nodes << std::endl;
        std::cout << "default time: " << duration1.count() << std::endl;
        std::cout << "optimized time: " << duration2.count() << std::endl;
    }
}