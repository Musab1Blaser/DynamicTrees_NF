#include <iostream>
#include <vector>
#include <map>
#include "ffnf.hpp"
#include "dt_nf.hpp"


int main(){
    std::vector<std::map<int, int>> adj (7);
    adj[1][2] = 10;
    adj[1][3] = 10;
    adj[2][3] = 10;
    adj[2][4] = 10;
    adj[2][5] = 1;
    adj[3][5] = 4;
    adj[4][5] = 3;
    adj[4][6] = 2;
    adj[5][6] = 10;
    int s = 1;
    int t = 6;
    int flow = dinicMaxFlow(s, t, adj);
    int flow2 = fordFulkerson(adj, s, t);
    std::cout << "The maximum flow in dt is: " << flow << std::endl;
    std::cout << "The maximum flow in ff is: " << flow2 << std::endl;
    return 0;

}                                                                                                                                                                                               