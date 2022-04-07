#ifndef LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_SIMULATEDANNEALING_H
#define LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_SIMULATEDANNEALING_H
#include "Node.h"
#include <vector>
#include <map>

using namespace std;

class SimulatedAnnealing {
public:
    SimulatedAnnealing(int, float, float, float);
    SimulatedAnnealing(map<int, Node>, int, float, float, float);
    void setGraph(map<int, Node>);
    void run(int);
    void chooseUtil();
    int getUtilNum();
    void setInt(float);
    void setTemperature(float);
    float getTemperature();
    int returnIterations();
    float returnCost();
    vector<int> returnPath();
private:
    float getCost(int, int);
    void anneal(vector<int>);
    float acception(float, float);
    float returnPathCost(vector<int>);
    vector<int> newPath(vector<int>);
    map<int, Node> graph;
    int iterations = 0;
    int utilNum;
    float tempMin;
    float decInt;
    Node src;
    float temperature;
    vector<int> path;
    float cost;
};


#endif //LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_SIMULATEDANNEALING_H