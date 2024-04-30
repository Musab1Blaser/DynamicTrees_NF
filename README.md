# DynamicTrees_NF
A Data Structures project on Dynamic Trees - specifically ST Link-Cut Trees. Our goal is to implement the data strucutres, visualise its operation, analyse its time complexity and use it to optimize network flow optimization.

g++ ST_Tree/src/main.cpp ST_Tree/src/ST_Tree.cpp ST_Tree/src/visualise.cpp -Wall -o ST_Tree.out

g++ graph/graph.cpp Network_Flow/*.cpp ST_Tree/src/ST_Tree.cpp ST_Tree/src/visualise.cpp -Wall -o prob_test.out
then plotting_flow.py

g++ ST_Tree/src/ST_Tree.cpp ST_Tree/src/testing_optimization.cpp -Wall -o optim_test.out
then plotting_optim.py