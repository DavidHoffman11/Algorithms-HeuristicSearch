#ifndef LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_DYNAMICPROGRAMMING_H
#define LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_DYNAMICPROGRAMMING_H
#include "Node.h"
#include <vector>
#include <map>

class DynamicProgramming {
public:
    static void load(map<int, Node>&, int);
    static void DynamicAlgo(Node);
    static float& returnCost();
    static int returnIterations();
    static vector<int> returnPath();
private:
    static float runAlgo(int, int);
    static float getCost(int, int, map<int, Node>&);
    static float cost;
    static int iterations;
    static vector<int> path;
    static int src;
    static vector<vector<float>> distTable;
    static vector<vector<float>> calc;
};


#endif //LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_DYNAMICPROGRAMMING_H
