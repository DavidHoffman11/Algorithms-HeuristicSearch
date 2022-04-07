#include "DynamicProgramming.h"
#include "Node.h"
#include "math.h"
#include <map>
#include <climits>
#include <vector>
#include <iostream>

using namespace std;

int DynamicProgramming::src = 0;
float DynamicProgramming::cost = 0;
int DynamicProgramming::iterations = 0;
vector<int> DynamicProgramming::path;
vector<vector<float>> DynamicProgramming::distTable;
vector<vector<float>> DynamicProgramming::calc;

void DynamicProgramming::load(map<int, Node>& graph, int x) {
    calc.resize(pow(2, graph.size()));

    for(int i = 0; i < calc.size(); i++) {
        for (int j = 0; j < graph.size(); j++) {
            calc[i].push_back(INT_MAX);
        }
    }  //fill up calc adjMatrix

    distTable.resize(graph.size());

    for(int row = 0; row < graph.size(); row++) {
        for (int col = 0; col < graph.size(); col++) {
            distTable[row].push_back(getCost(row + 1, col + 1, graph));
        }
    }  //fill up distTable adjMatrix
}

void DynamicProgramming::DynamicAlgo(Node src) {
    iterations = 0;
    //initialize iterations to zero
    cost = runAlgo(1, src.getData() - 1);

    for (int i = 0; i < calc.size(); i++){
        for(int j = 0; j < distTable.size(); j++){
            if (calc[i][j] != INT_MAX) {
                bool temp = true;
                for(int n : path) {
                    if (n == j + 1) {
                        temp = false;
                    }
                }
                if(temp) {
                    path.push_back(j + 1);
                }
            }
        }
    }  //gets path
}

float& DynamicProgramming::returnCost() {
    return cost;
}

int DynamicProgramming::returnIterations() {
    return iterations;
}

vector<int> DynamicProgramming::returnPath() {
    return path;
}

float DynamicProgramming::runAlgo(int visited, int pos){
    iterations++;
    //counts iterations

    if(visited == (1 << distTable.size()) - 1) {
        return distTable[pos][0];
    }  //returns distance from last node to starting point if the index of the calc vector is equal to the last index

    if(calc[visited][pos] != INT_MAX) {
        return calc[visited][pos];
    }  //return distance if it has been found

    for(int i = 0; i < distTable.size(); i++){
        if((visited & (1 << i)) == 0) {
            //gets distance
            float temp = distTable[pos][i] +  runAlgo(visited | (1 << i), i);
            if(temp < calc[visited][pos]) {
                calc[visited][pos] = temp;
            }  //if distance is less than current distance, replace it
        }  //if node hasn't been visited, get distance
    }  //loops through list

    return calc[visited][pos];
}

float DynamicProgramming::getCost(int src, int dest, map<int, Node>& graph){
    float num = pow(graph[dest].getPosition()[0] - graph[src].getPosition()[0], 2);
    num += pow(graph[dest].getPosition()[1] - graph[src].getPosition()[1], 2);
    num += pow(graph[dest].getPosition()[2] - graph[src].getPosition()[2], 2);
    //gets distance^2 between x, y, and z positions

    return sqrt(num);
}
