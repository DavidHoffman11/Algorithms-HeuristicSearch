#ifndef LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_RUNTSP_H
#define LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_RUNTSP_H
#include "Node.h"
#include "Algorithm.h"
#include "GeneticAlgorithm.h"
#include "SimulatedAnnealing.h"
#include <iostream>
#include <map>
#include <chrono>
#include <vector>

using namespace std;

class RunTSP: public Algorithm {
public:
    RunTSP();
    ~RunTSP();
    void load();
    void execute();
    void display();
    void stats();
    void select(int);
    void save();
private:
    map<int, Node> graph;
    chrono::duration<double> runTime;
    GeneticAlgorithm* geneticAlgo;
    SimulatedAnnealing* simAnnealing;
    vector<int> bestPath;
    int algoExecute;
    int numIterations;
    float lowestDistance;
    Node src, dest;
};


#endif //LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_RUNTSP_H
