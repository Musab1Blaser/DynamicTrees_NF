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
    std::vector<std::map<int, std::pair<int, int>>> graph (numNodes);
    srand(time(0));
    // srand(1);
    for (int i = 1; i < numNodes; ++i) {
        for (int j = 1; j < numNodes; ++j) {
            int prob = rand() % 100;
            if (i != j and prob<30) {
                int weight = rand() % maxWeight + 1; // random weight from 1 to maxWeight
                graph[i][j] = {weight, 0};
            }
        }
    }
    return graph;
};

int main() {
    vector<int> numNodes = {10, 20, 30, 40, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 2500, 3000};
    std::ofstream outFile("duration.txt");
    std::ofstream outFile2("duration2.txt");
    std::ofstream outFile3("duration3.txt");
    for (int i=0; i<numNodes.size(); i++){
        std::vector<std::map<int, std::pair<int, int>>> graph = generateRandomGraph(numNodes[i]+1, int(numNodes[i]) ); //max weight = 50
        auto timeByFordstart = std::chrono::high_resolution_clock::now();
        //cout << timeByFordstart << endl;
        int maxFlow = fordFulkerson(graph, 1, numNodes[i]); //start to end
        auto timeByFordend = std::chrono::high_resolution_clock::now();
        auto timeByDTstart = std::chrono::high_resolution_clock::now();
        int maxFlow2 = DinicMaxflow(1, numNodes[i], graph, false);
        auto timeByDTend = std::chrono::high_resolution_clock::now();
        auto timeByDTstart2 = std::chrono::high_resolution_clock::now();
        int maxFlow3 = DinicMaxflow(1, numNodes[i], graph, true);
        auto timeByDTend2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = timeByFordend - timeByFordstart;
        std::chrono::duration<float> duration2 = timeByDTend - timeByDTstart;
        std::chrono::duration<float> duration3 = timeByDTend2 - timeByDTstart2;
        outFile << "x: " << numNodes[i] << ", y: " << duration.count() << " seconds\n";
        outFile2 << "x: " << numNodes[i] << ", y: " << duration2.count() << " seconds\n";
        outFile3 << "x: " << numNodes[i] << ", y: " << duration3.count() << " seconds\n";
        // cout << "maxflow "<<maxFlow<<" "<<   (maxFlow == maxFlow2) << endl;
        std::cout << numNodes[i]<<std::endl;
        if (maxFlow != maxFlow2 or maxFlow != maxFlow3){
            cout << "Error: max flow is not the same" << endl;
        }
        cout << "maxflow 1 "<< maxFlow << " - " << duration.count() <<" maxflow 2 "<<maxFlow2 << " - " << duration2.count()<<" maxflow 3 "<<maxFlow3 << " - " << duration3.count() << endl;
        //cout << "max flow from source to sink: " << maxFlow << endl;
    }
    outFile.close();

    return 0;
}