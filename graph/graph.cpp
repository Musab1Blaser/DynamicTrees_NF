#include <iostream>
#include <unordered_set>
#include <unordered_map> //dictionary
#include <queue>
#include <climits>
#include <fstream>
#include<cstdlib>
#include<thread>
#include <chrono>
#include <map>
#include "../Network_Flow/ffnf.hpp"
#include "../Network_Flow/dt_nf.hpp"

using namespace std;


std::vector<std::map<int, std::pair<int, int>>> generateRandomGraph(int numNodes, int maxWeight) {
    std::vector<std::map<int, std::pair<int, int>>> graph(numNodes);

    for (int i = 0; i < numNodes; ++i) {
        for (int j = i; j < numNodes; ++j) {
            int prob = rand() % 100;
            if (i != j and prob<10) {
                int weight = rand() % maxWeight + 1; // random weight from 1 to maxWeight
                graph[i][j] = {weight, 0};
            }
        }
    }

    //printing graph
    // for (int i = 0; i < numNodes; i++){
    //     for (int j = 0; j < numNodes; ++j){
    //         if (i!=j){
    //         cout << "between " << i << " and " << j << " " << graph[i][j] << endl;
    //         }
    //     }
    // }

    return graph;
};

int main() {
    vector<int> numNodes = {50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    std::ofstream outFile("duration.txt");
    std::ofstream outFile2("duration2.txt");
    for (int i=0; i<numNodes.size(); i++){
        std::vector<std::map<int, std::pair<int, int>>> graph = generateRandomGraph(numNodes[i], int(numNodes[i]/10) ); //max weight = 50
        auto timeByFordstart = std::chrono::high_resolution_clock::now();
        //cout << timeByFordstart << endl;
        int maxFlow = fordFulkerson(graph, 0, numNodes[i]-1); //start to end
        auto timeByFordend = std::chrono::high_resolution_clock::now();
        auto timeByDTstart = std::chrono::high_resolution_clock::now();
        int maxFlow2 = DinicMaxflow(0, numNodes[i]-1, graph);
        auto timeByDTend = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration2 = timeByDTend - timeByDTstart;
        std::chrono::duration<float> duration = timeByFordend - timeByFordstart;
        outFile << "x: " << numNodes[i] << ", y: " << duration.count() << " seconds\n";
        outFile2 << "x: " << numNodes[i] << ", y: " << duration2.count() << " seconds\n";
        //cout << "max flow from source to sink: " << maxFlow << endl;
    }
    outFile.close();

    return 0;
}