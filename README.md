# DynamicTrees_NF
A Data Structures project on Dynamic Trees - specifically ST Link-Cut Trees. We have implemented implemented the data strucutre, visualised it across operations and analysed its time complexity while using it to optimize network flow algorithms.

Our project report is in the report directory.

For compiling and running our programs, please refer to the instructions below (note that you may have to modify the *.out* extension in compilation as per your operating system):
1. For an interactive environment to test the data structure, firstly compile with the following command: <br>
```g++ ST_Tree/src/main.cpp ST_Tree/src/ST_Tree.cpp ST_Tree/src/visualise.cpp -Wall -o ST_Tree.out```
<br>
Then run the compiled program with *./ST_Tree.out a b c d* where *a, b, c, d* are numbers that do the following:
<br>
    - *a* represents visualisation mode for actual graph, 0 - no visualisation, 1 - visualise but don't load automatically, 2 - visualise and load <br> <br>
    - *b* represents visualisation mode of internal graph, 0 - no visualisation, 1 - visualise but don't load automatically, 2 - visualise and load <br> <br>
    - *c* represents debug mode, 0 - no debugging visualisation, 1 - create graph + provide log after certain internal operations <br> <br>
    - *d* represents whether to use sample graph or no, 0 - no sample graph, 1 - work on sample graph <br> <br>

2. To test performance of network flow algorithms, you may use the pre-existing *low_prob_test.out* and *high_prob_test.out* or compile your own using: <br>
```g++ graph/graph.cpp Network_Flow/*.cpp ST_Tree/src/ST_Tree.cpp ST_Tree/src/visualise.cpp -Wall -o prob_test.out``` <br>
Then run the compiled program with *./prob_test.out* <br>
You can see the results being generated in real-time. Once all results are generated, you may plot the results by running *plotting_flow.py*

3. To compare the performance of the optimized and unoptimized Dynamic Tree, you may use the pre-existing *optim_test.out* or compile your own using: <br>
```g++ ST_Tree/src/ST_Tree.cpp ST_Tree/src/testing_optimization.cpp -Wall -o optim_test.out``` <br>
Then run the compiled program with *./optim_test.out* <br>
You can see the results being generated in real-time. Once all results are generated, you may plot the results by running *plotting_optim.py*

We really enjoyed working on this project. The ideas presented in the papers were incredibly creative, the process of working out the implementation was challenging, but so fulfilling, and the whole experience has been incredibly enriching.

We hope the resources we have developed can be of help to others exploring this wonderful topic.

Enjoy!