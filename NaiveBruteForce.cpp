#include "NaiveBruteForce.h"
#include "Node.h"
#include <math.h>
#include <stdio.h>
#include <map>
#include <climits>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

float NaiveBruteForce::cost = 0;
int NaiveBruteForce::iterations = 0;
vector<int> NaiveBruteForce::path;

void NaiveBruteForce::NaiveAlgo(map<int, Node> &graph, Node src) {
    vector<int> nodes;
    //list of nodes in graph
    map<int, Node>::iterator it;

    cost = INT_MAX;
    //min value

    for ( it = graph.begin(); it != graph.end(); it++) {
        if (src != it->first) {
            nodes.push_back(it->first);
        }
    }  //fill vector of nodes

    do {
        iterations++;
        //keeps track of iterations

        float current_distance = 0;
        //stores distance of current path

        Node tempSrc = src;

        //compute total distance of current path
        for (int i = 0; i < nodes.size(); i++) {
            current_distance += getDistance(tempSrc, nodes[i], graph);
            tempSrc = nodes[i];
        }
        current_distance += getDistance(tempSrc, src, graph);

        if (current_distance < cost) {
            path = nodes;
        }  //changes the path variable if current cost is shorter than the cost of the current path

        cost = fmin(cost, current_distance);
    } while (next_permutation(nodes.begin(), nodes.end()));
    //executes while there are still permutations in the vector
}  //based on code from https://iq.opengenus.org/travelling-salesman-problem-brute-force/

float& NaiveBruteForce::returnCost() {
    return cost;
}

int NaiveBruteForce::returnIterations() {
    return iterations;
}

vector<int>& NaiveBruteForce::returnPath() {
    return path;
}

float NaiveBruteForce::getDistance(Node src, Node dest, map<int, Node>& graph) {
    float num = pow(graph[dest.getData()].getPosition()[0] - graph[src.getData()].getPosition()[0], 2);
    num += pow(graph[dest.getData()].getPosition()[1] - graph[src.getData()].getPosition()[1], 2);
    num += pow(graph[dest.getData()].getPosition()[2] - graph[src.getData()].getPosition()[2], 2);

    return sqrt(num);
    //returns distance
}