#include "SimulatedAnnealing.h"
#include "Node.h"
#include "math.h"
#include <vector>
#include <map>
#include <ctime>
#include <cassert>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing(int x, float tempValue, float minValue, float intValue) {
    src = x;
    temperature = tempValue;
    tempMin = minValue;
    decInt = intValue;
}

SimulatedAnnealing::SimulatedAnnealing(map<int, Node> g, int x, float tempValue, float minValue, float intValue) {
    graph = g;
    src = x;
    temperature = tempValue;
    tempMin = minValue;
    decInt = intValue;
}

void SimulatedAnnealing::setGraph(map<int, Node> g) {
    graph = g;
}

void SimulatedAnnealing::run(int x) {
    vector<int> currPath;
    src.setData(x);

    for(int i = 1; i <= graph.size(); i++) {
        if (i != src.getData()) {
            currPath.push_back(i);
        }
    }  //creates first possible path

    anneal(currPath);
      //runs algorithm
}

void SimulatedAnnealing::chooseUtil() {
    srand(time(NULL));
    utilNum = rand() % 2;
}

int SimulatedAnnealing::getUtilNum() {
    return utilNum;
}

void SimulatedAnnealing::setInt(float x) {
    decInt = x;
}

void SimulatedAnnealing::setTemperature(float x) {
    temperature = x;
}

float SimulatedAnnealing::getTemperature() {
    return temperature;
}

int SimulatedAnnealing::returnIterations() {
    return iterations;
}

float SimulatedAnnealing::returnCost() {
    return cost;
}

vector<int> SimulatedAnnealing::returnPath() {
    return path;
}

float SimulatedAnnealing::getCost(int src, int dest) {
    float num = pow(graph[dest].getPosition()[0] - graph[src].getPosition()[0], 2);
    num += pow(graph[dest].getPosition()[1] - graph[src].getPosition()[1], 2);
    num += pow(graph[dest].getPosition()[2] - graph[src].getPosition()[2], 2);
      //gets distance^2 between x, y, and z positions

    return sqrt(num);
}
void SimulatedAnnealing::anneal(vector<int> vec) {
    float oldCost = returnPathCost(vec);
    float accept;

    while(temperature > tempMin) {
        for(int i = 0; i < (vec.size() * 10); i++) {
            vector<int> newPath = SimulatedAnnealing::newPath(vec);
            float newCost = returnPathCost(newPath);
              //gets new path and its cost

            accept = acception(newCost, oldCost);

            float randomInt = ((float) rand() / (RAND_MAX));

            if(accept > randomInt) {
                oldCost = newCost;
                vec = newPath;
            }
            iterations++;
        }

        temperature *= (1 - decInt);
        iterations++;
    }

    cost = oldCost;
    path = vec;
}

float SimulatedAnnealing::acception(float newCost, float oldCost) {
    float exponent = (oldCost - newCost) / temperature;

    return exp(exponent);
}

float SimulatedAnnealing::returnPathCost(vector<int> vec) {
    float cost = getCost(src.getData(), vec[0]);

    for (int i = 0; i < vec.size() - 1; i++) {
        cost += getCost(vec[i], vec[i + 1]);
    }

    return (cost + getCost(vec[vec.size() - 1], src.getData()));
}

vector<int> SimulatedAnnealing::newPath(vector<int> vec) {
    vector<int> newPath = vec;

    int index1 = rand() % vec.size();
    int index2 = rand() % vec.size();
      //swap two random numbers

    while(index1 == index2) {
        index1 = rand() % vec.size();
        index2 = rand() % vec.size();
    }

    std::swap(newPath[index1], newPath[index2]);

    return newPath;
      //return new path
}