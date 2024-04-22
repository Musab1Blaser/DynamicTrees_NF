#pragma once
#include "../ST_Tree/src/ST_Tree.hpp"
#include "../ST_Tree/src/visualise.hpp"
#include <queue>
#include <vector>
#include <list>
std::vector<std::map<int, int>> adj_inv(std::vector<std::map<int, int>> adj);
int dinicMaxFlow(int s, int t, std::vector<std::map<int, int>> adj);
int blockingPaths(int s, int t, std::vector<std::map<int, std::pair<int, int>>>& adj, std::vector<int>& start, std::vector<int>& level, bool optim);
int DinicMaxflow(int s, int t, std::vector<std::map<int, std::pair<int, int>>> adj, bool optim = false);