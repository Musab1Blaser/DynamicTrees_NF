#pragma once
#include <unordered_map>
#include <map>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;
int fordFulkerson(std::vector<std::map<int, std::pair<int, int>>> graph, int source, int sink);