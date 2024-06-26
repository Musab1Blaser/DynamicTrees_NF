// #include <iostream>
// #include <vector>
// #include <map>
// #include "ffnf.hpp"
// #include "dt_nf.hpp"
// #include <chrono>

// int main(){
//     // std::vector<std::map<int, int>> adj (7);
//     // adj[1][2] = 16;
//     // adj[1][3] = 13;
//     // adj[2][3] = 10;
//     // adj[2][4] = 12;
//     // adj[3][2] = 4;
//     // adj[3][5] = 14;
//     // adj[4][3] = 9;
//     // adj[4][6] = 20;
//     // adj[5][4] = 7;
//     // adj[5][6] = 4;


//     std::vector<std::map<int, std::pair<int, int>>> adj (7);
//     adj[1][2] = {16, 0};
//     adj[1][3] = {13, 0};
//     adj[2][3] = {10, 0};
//     adj[2][4] = {12,0};
//     adj[3][2] = {4, 0};
//     adj[3][5] = {14, 0};
//     adj[4][3] = {9, 0};
//     adj[4][6] = {20, 0};
//     adj[5][4] = {7, 0};
//     adj[5][6] = {4, 0};
//     int s = 1;
//     int t = 6;
//     auto timeByDTstart = std::chrono::high_resolution_clock::now();
//     int flow = DinicMaxflow(s, t, adj, false);
//     auto timeByDTend = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<float> duration2 = timeByDTend - timeByDTstart;
//     auto timeByFFstart = std::chrono::high_resolution_clock::now();
//     int flow2 = fordFulkerson(adj, s, t);
//     auto timeByFFend = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<float> duration1 = timeByFFend - timeByFFstart;
//     std::cout << "The maximum flow in dt is: " << flow << std::endl;
//     std::cout << "Time taken by dt: " << duration2.count() << " seconds" << std::endl;
//     std::cout << "The maximum flow in ff is: " << flow2 << std::endl;
//     std::cout << "Time taken by ff: " << duration1.count() << " seconds" << std::endl;
//     return 0;

// }                                                                                                                                                                                               