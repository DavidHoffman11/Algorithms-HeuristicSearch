#include "GeneticAlgorithm.h"
#include "Node.h"
#include "math.h"
#include <vector>
#include <map>
#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(map<int, Node>& g, int pop, int generation, int mutate) {
    if((pop > 1) && (mutate >= 0 && mutate <= 100)) {
        adjPopSize = 0;
        graph = g;
        popSize = pop;
        gens = generation;
        mutRate = mutate;
    }
}

void GeneticAlgorithm::crossover1(vector<int>& vec1, vector<int>& vec2) {
    vector<int> c1, c2;

    map<int, int> map1, map2;

    for(int i = 0; i < graph.size() - 1; i++) {
        map1[vec1[i]] = 0;
        map2[vec2[i]] = 0;
    }  //checks to see if map have been checked yet

    int p1 = rand() % (graph.size() - 2) + 1;
    int p2 = rand() % (graph.size()  - 1 - p1) + p1;

    if(p1 == p2) {
        if(p1 - 1 > 1) {
            p1--;
        } else if(p2 + 1 < (graph.size() - 1)) {
            p2++;
        } else {
            int p = rand() % 10 + 1;
            if(p <= 5) {
                p1--;
            } else {
                p2++;
            }
        }
    }

    for(int i = 0; i < p1; i++) {
        c1.push_back(vec1[i]);
        c2.push_back(vec2[i]);
          //adds map
        map1[vec1[i]] = 1;
        map2[vec2[i]] = 1;
          //marks map
    }

    for(int i = p2 + 1; i < graph.size() - 1; i++) {
        map1[vec1[i]] = 1;
        map2[vec2[i]] = 1;
    }  //remaining map are marked

    for(int i = p2; i >= p1; i--) {
        if(map1[vec2[i]] == 0 && vec2[i] > 0 && vec2[i] <= graph.size()){
            c1.push_back(vec2[i]);
              //marks gene as used
            map1[vec2[i]] = 1;
        } else {
            //if the gene already is used chooses gene that is not used
            for(map<int, int>::iterator it = map1.begin(); it != map1.end(); ++it) {
                if(it->second == 0 && it->first > 0 && it->first <= graph.size()) {
                    c1.push_back(it->first);
                    map1[it->first] = 1;
                    break;
                }  //checks if gene is not used
            }
        }

        if(map2[vec1[i]] == 0 && vec1[i] > 0 && vec2[i] <= graph.size()) {
            c2.push_back(vec1[i]);
            map2[vec1[i]] = 1;
        }else {
            for(map<int, int>::iterator it = map2.begin(); it != map2.end(); ++it){
                //checks if gene is used
                if(it->second == 0 && it->first > 0 && it->first <= graph.size()){
                    //adds it to child, mark it as used and breaks
                    c2.push_back(it->first);
                    map2[it->first] = 1;
                    break;
                }
            }
        }
    }

    for(int i = p2 + 1; i < graph.size() - 1; i++){
        c1.push_back(vec1[i]);
        c2.push_back(vec2[i]);
    }  //child1 receives remaining map of parent1 and child2 receives remaining map of parent2

    srand((unsigned)time(NULL));

    int mutation = rand() % 100 + 1;

    if(mutation <= mutRate) {
        chooseMutation();
          //mutation is randomly selected
        if(mutationNum == 0) {
            mutation1(c1, c2);
        } else {
            mutation2(c1, c2);
        }  //mutates based on which function is selected
    }
}

void GeneticAlgorithm::crossover2(vector<int>& vec1, vector<int>& vec2) {
    vector<int> c1, c2;

    int vecSize1 = vec1.size();
    int vecSize2 = vec2.size();

    for(int i = 0; i < vecSize1; i++) {
        if(i < vecSize1/2) {
            c1.push_back(vec1[i]);
        } else {
            c1.push_back(vec2[i]);
        }
    }  //fills child1 with half of one parent and half of the other

    for(int i = 0; i < vecSize2; i++) {
        if(i < vecSize2/2) {
            c2.push_back(vec2[i]);
        } else {
            c2.push_back(vec1[i]);
        }
    }  //fills child2 with half of one parent and half of the other

    srand((unsigned)time(NULL));

    int mutation = rand() % 100 + 1;

    if(mutation <= mutRate) {
        chooseMutation();
        //mutation is randomly selected
        if(mutationNum == 0) {
            mutation1(c1, c2);
        } else {
            mutation2(c1, c2);
        }  //mutates based on which function is selected
    }
}

void GeneticAlgorithm::mutation1(vector<int>& vec1, vector<int>& vec2) {
    srand((unsigned)time(NULL));

    int geneIndex1 = rand() % (graph.size() - 2) + 1;
    int geneIndex2 = rand() % (graph.size() - 2) + 1;

    rotate(vec1.begin(), vec1.begin() + geneIndex1, vec1.end());
    rotate(vec2.begin(), vec2.begin() + geneIndex2, vec2.end());
      //mutate children

    float cost1 = isSolution(vec1);
    float cost2 = isSolution(vec2);
      //get cost of child paths

    if(cost1 != -1 && ! doesExist(vec1)) {
        insert(vec1, cost1);
        adjPopSize++;
    }
    if(cost2 != -1 && ! doesExist(vec2)) {
        insert(vec2, cost2);
        adjPopSize++;
    }
}

void GeneticAlgorithm::mutation2(vector<int>& vec1, vector<int>& vec2) {
    srand((unsigned)time(NULL));

    int geneIndex1 = rand() % (graph.size() - 2) + 1;
    int geneIndex2 = rand() % (graph.size() - 2) + 1;

    swap(vec1[geneIndex1], vec1[geneIndex2]);
    swap(vec2[geneIndex1], vec2[geneIndex2]);
      //mutate children

    float cost1 = isSolution(vec1);
    float cost2 = isSolution(vec2);
      //get cost of child paths

    if(cost1 != -1 && ! doesExist(vec1)) {
        insert(vec1, cost1);
        adjPopSize++;
    }
    if(cost2 != -1 && ! doesExist(vec2)) {
        insert(vec2, cost2);
        adjPopSize++;
    }
}

pair<int, int> GeneticAlgorithm::selection1() {
    int parent1, parent2;

    do {
        srand((unsigned)time(NULL));
        parent1 = rand() % adjPopSize;
        parent2 = rand() % adjPopSize;
    } while(parent1 == parent2);

    return make_pair(parent1, parent2);
}

pair<int, int> GeneticAlgorithm::selection2() {
    float totalFitness = 0;
    float currentFitness = 0;
    int parent1, parent2;

    for (int i = 0; i < population.size(); i++) {
        totalFitness += population[i].second;
    }

    srand((unsigned)time(NULL));
    float random1 = (float)(((float)rand()/(RAND_MAX)) * totalFitness);
    float random2 = (float)(((float)rand()/(RAND_MAX)) * totalFitness);

    for (int i = 0; i < population.size(); i++) {
        currentFitness += population[i].second;
          //sets parent if number is in range
        if(currentFitness >= random1) {
            parent1 = i;
        }
        if(currentFitness >= random2) {
            parent2 = i;
        }
    }

    return make_pair(parent1, parent2);
}

void GeneticAlgorithm::chooseCrossover() {
    srand(time(NULL));
    crossoverNum = rand() % 2;
}

int GeneticAlgorithm::getCrossover() {
    return crossoverNum;
}

void GeneticAlgorithm::chooseMutation() {
    srand(time(NULL));
    mutationNum = rand() % 2;
}

int GeneticAlgorithm::getMutation() {
    return mutationNum;
}

void GeneticAlgorithm::chooseSelect() {
    srand(time(NULL));
    selectionNum = rand() % 2;
}

int GeneticAlgorithm::getSelection() {
    return selectionNum;
}

float GeneticAlgorithm::isSolution(vector<int>& vec) {
    map<int, int> countMap;

    for (int i = 0; i < vec.size(); i++) {
        countMap[i]++;
    }   //stores frequency

    for (pair<int, int> pair : countMap) {
        if (pair.second > 1) {
            return -1;
        }  //returns -1 if on a repeating value
    }


    float cost = getCost(src.getData(), vec[0]);

    for(int i = 0; i < vec.size() - 1; i++) {
        cost += getCost(vec[i], vec[i + 1]);
    }  //if solution is correct, calculate solution

    cost += getCost(vec[vec.size() - 1], src.getData());


    return cost;
}

void GeneticAlgorithm::insert(vector<int>& path, float cost) {
    int min = 0;
    int max = adjPopSize - 1;

    while(max >= min) {
        int mid = min + (max - min) / 2;
        if(cost == population[mid].second) {
            population.insert(population.begin() + mid, make_pair(path, cost));
            return;
        } else if(cost > population[mid].second) {
            min = mid + 1;
        } else {
            max = mid - 1;
        }
    }

    population.insert(population.begin() + min, make_pair(path, cost));
}

void GeneticAlgorithm::run(Node x) {
    src = x;
    initPop(src);
    iterations++;


    if(adjPopSize == 0) {
        return;
    }  //returns if population is 0

    for(int i = 0; i < gens; i++) {
        iterations++;
        int oldPopSize = adjPopSize;
          //sets original pop size equal to adjusted pop size

        if(adjPopSize >= 2) {
            if(adjPopSize == 2) {
                chooseCrossover();
                  //randomly selects which crossover method to use
                if(crossoverNum == 0) {
                    crossover1(population[0].first, population[1].first);
                } else {
                    crossover2(population[0].first, population[1].first);
                }
            } else {
                pair<int, int> parents;
                chooseSelect();
                  //randomly chooses which selection method to use
                if(selectionNum == 0) {
                    parents = selection1();
                } else {
                    parents = selection2();
                }
                chooseCrossover();
                //randomly selects which crosover method to use
                if(crossoverNum == 0) {
                    crossover1(population[0].first, population[1].first);
                } else {
                    crossover2(population[0].first, population[1].first);
                }
            }

            int diffPop = adjPopSize - oldPopSize;

            if(diffPop == 2) {
                if(adjPopSize > popSize) {
                    population.pop_back();
                    population.pop_back();
                    adjPopSize -= 2;
                }  //removes worst 2 elements and adjusts size accordingly
            } else if(diffPop == 1) {
                if(adjPopSize > popSize) {
                    population.pop_back();
                    adjPopSize--;
                }  //removes worst elements and adjusts size accordingly
            }
        } else {
            crossover1(population[0].first, population[0].first);
            if(adjPopSize > popSize) {
                population.pop_back();
                adjPopSize--;
            } //removes worst elements and adjusts size accordingly
        }
    }

    path = population[0].first;
    cost = population[0].second;
      //sets path and cost equal to the best path and cost from the population
}

bool GeneticAlgorithm::doesExist(vector<int>& vec) {
    for (int i = 0; i < population.size(); i++) {
        if (population[i].first == vec) {
            return true;
        }
    }

    return false;
}

bool GeneticAlgorithm::sort(const pair<vector<int>, float>& vec1, const pair<vector<int>, float>& vec2) {
    return (vec1.second < vec2.second);
}

float GeneticAlgorithm::returnCost() {
    return cost;
}

int GeneticAlgorithm::returnIterations() {
    return iterations;
}

vector<int> GeneticAlgorithm::returnPath() {
    return path;
}

float GeneticAlgorithm::getCost(int src, int dest) {
    float num = pow(graph[dest].getPosition()[0] - graph[src].getPosition()[0], 2);
    num += pow(graph[dest].getPosition()[1] - graph[src].getPosition()[1], 2);
    num += pow(graph[dest].getPosition()[2] - graph[src].getPosition()[2], 2);
    //gets distance^2 between x, y, and z positions

    return sqrt(num);
}

void GeneticAlgorithm::initPop(Node src) {
    vector<int> parent;

    for(int i = 0; i < graph.size(); i++) {
        if (i + 1 != src.getData()) {
            parent.push_back(i + 1);
        }
    }

    float totalCost = isSolution(parent);

    if(totalCost != -1) {
        totalCost += getCost(src.getData(), parent[0]);
          //add cost from source to first node
        population.push_back(make_pair(parent, totalCost));
        adjPopSize++;
    }

    for(int i = 0; i < gens; i++) {
        random_shuffle(parent.begin(), parent.end());
        totalCost = isSolution(parent);
        if(totalCost != -1 && ! doesExist(parent)) {
            totalCost += getCost(src.getData(), parent[0]);
              //add cost from source to first node
            population.push_back(make_pair(parent, totalCost));
            adjPopSize++;
        }
        if(adjPopSize == popSize) {
            break;
        }
    }

    if(adjPopSize != 0) {
        std::sort(population.begin(), population.end(), sort);
    }
}