#include "ST_Tree.hpp"

// int main()
// {
//     // tree to represent:
//     // std::map<int, int> treePar = {{2, 1}, {6, 5}, {4, 2}, {5, 2}, {3, 1}};

//     //       1
//     //     /   \
//     //    3     2
//     //        /   \
//     //       4     5
//     //              \
//     //               6

//     ST_Tree ST = ST_Tree(6); // Initialise ST-Tree with 6 nodes numbered 1, 2, ..., 6
//     ST.link(2, 1, 0); // make 1 the parent of 2
//     ST.link(6, 5, 0); // make 5 the parent of 6
//     ST.link(4, 2, 0); // make 2 the parent of 4
//     ST.link(5, 2, 0); // make 2 the parent of 5 - makes 2-4 connection dashed
//     ST.link(3, 1, 0); // make 1 the parent of 3 - makes 1-2 connection dashed
    
//     // can also directly initialise - gives slightly different output as links added in sorted order, instead of provided order
//     // ST_Tree ST = ST_Tree(treePar, 6);

//     ST.cut(2); // break tree edge par(2)-2 -> result 1.3 and 4.2.5-6 (. signifies dashed edge) 
// }