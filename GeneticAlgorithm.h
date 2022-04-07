#ifndef LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_GENETICALGORITHM_H
#define LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_GENETICALGORITHM_H
#include "Node.h"
#include <vector>
#include <map>

using namespace std;

class GeneticAlgorithm {
public:
    GeneticAlgorithm(map<int, Node>&, int, int, int);
    void crossover1(vector<int>&, vector<int>&);
      //runs a multi-point crossover
    void crossover2(vector<int>&, vector<int>&);
      //runs a one-point crossover
    void mutation1(vector<int>&, vector<int>&);
    void mutation2(vector<int>&, vector<int>&);
    pair<int, int> selection1();
    pair<int, int> selection2();
    void chooseCrossover();
    void chooseMutation();
    void chooseSelect();
    int getCrossover();
    int getMutation();
    int getSelection();
    float isSolution(vector<int>&);
    void insert(vector<int>&, float);
    void run(Node);
    bool doesExist(vector<int>&);
    static bool sort(const pair<vector<int>, float>&, const pair<vector<int>, float>&);
    float returnCost();
    int returnIterations();
    vector<int> returnPath();

private:
    float getCost(int, int);
    void initPop(Node);
    map<int, Node> graph;
    vector<pair<vector<int>, float>> population;
    vector<int> path;
    int mutRate;
    int popSize;
    int adjPopSize;
    int gens;
    float cost;
    Node src = 1;
    int selectionNum = 0;
    int mutationNum = 0;
    int crossoverNum = 0;
    int iterations = 0;
};


#endif //LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_GENETICALGORITHM_H
