#include "RunTSP.h"
#include "GeneticAlgorithm.h"
#include "SimulatedAnnealing.h"
#include "NaiveBruteForce.h"
#include "DynamicProgramming.h"
#include <iostream>
#include <fstream>

using namespace std;

RunTSP::RunTSP() {
    load();
    geneticAlgo = new GeneticAlgorithm(graph, 400, 800, 15);
}

RunTSP::~RunTSP() {
    delete geneticAlgo;
    delete simAnnealing;
}

void RunTSP::load() {
    string file1 = "Data/Graph/testGraph.txt";
      //stores graph.txt
    string file2 = "Data/Graph/testPositions.txt";
      //stores positions.txt

    src.setData(1);
      //sets source node equal to 1

    ifstream file(file1);
    if(!file){
        cout << "Could not load " << file1 << endl;
        perror ( "Stream Failed to open because: " );
        return;
    }  //prints error statement if file can't be loaded in

    else if(file.is_open()) {
        string source, destination, token;
        string delim = ",";
        size_t pos = 0;

        while (getline(file, source, ',')) {
            Node temp(stoi(source));
              //read in source node
            int x = stoi(source);

            getline(file, destination);
              //get connected nodes
            while ((pos = destination.find(delim)) != string::npos) {
                token = destination.substr(0, pos);
                temp.setConnections(Node(stoi(token)));
                destination.erase(0, pos + delim.length());
                  //adds connected nodes to connectedNodes vector
            }
            temp.setConnections(Node(stoi(destination)));
              //add last int in list to vector
            graph.insert({x, temp});
        }
    }
    file.close();

    file.open(file2);
    if (file.is_open()) {
        string source;
          //holds int value of source node
        string x, y, z;
          //holds position value of source
        while (getline(file, source, ',') && getline(file, x, ',') && getline(file, y, ',') && getline(file, z, '\n')) {
            (graph)[stoi(source)].setPosition(stoi(x), stoi(y), stoi(z));
              //add position to source node
            if((graph)[stoi(source)].getData() == src.getData()) {
                src.setPosition(stoi(x), stoi(y), stoi(z));
            } else if((graph)[stoi(source)].getData() == dest.getData()) {
                dest.setPosition(stoi(x), stoi(y), stoi(z));
            }  //if/else statement sets position of src and dest node once that node is found
        }
    }
    file.close();
}

void RunTSP::execute() {
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

      //executes the different algorithms
    if(algoExecute == 0 || algoExecute == 1 || algoExecute == 2 || algoExecute == 3) {
        if (algoExecute == 0) {
              //run TSP Naive
            NaiveBruteForce::NaiveAlgo(graph, src);
            lowestDistance = NaiveBruteForce::returnCost();
            numIterations = NaiveBruteForce::returnIterations();
            bestPath = NaiveBruteForce::returnPath();
        } else if (algoExecute == 1) {
              //run TSP Dynamic
            DynamicProgramming::load(graph, 1);
            DynamicProgramming::DynamicAlgo(src);
            lowestDistance = DynamicProgramming::returnCost();
            numIterations = DynamicProgramming::returnIterations();
            bestPath = NaiveBruteForce::returnPath();
        } else if (algoExecute == 2) {
              //run genetic algo
            geneticAlgo->run(src);
            lowestDistance = geneticAlgo->returnCost();
            bestPath = geneticAlgo->returnPath();
            numIterations = geneticAlgo->returnIterations();
        } else if (algoExecute == 3) {
              //run Simulated Annealing
            simAnnealing->run(src.getData());
            lowestDistance = simAnnealing->returnCost();
            bestPath = simAnnealing->returnPath();
            numIterations = simAnnealing->returnIterations();
        }
    }

    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    runTime = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
}


void RunTSP::display() {
    cout << "Path: " << "1";

    for(int n : bestPath) {
        cout << " -> " << n;
    }  //loops through vector and outputs path
    cout << " -> " << "1" << endl;
}

void RunTSP::stats() {
    if(algoExecute == 0) {
        cout << "--------STATS FOR NAIVE BRUTE FORCE--------" << endl;
        display();
          //calls display function which actually displays the path
    } else if(algoExecute == 1) {
        cout << "--------STATS FOR DYNAMIC PROGRAMMING--------" << endl;
        display();
          //calls display function which actually displays the path
    } else if(algoExecute == 2) {
        cout << "--------STATS FOR GENETIC ALGORITHM--------" << endl;
        display();
          //calls display function which actually displays the path
        cout << "Selection Technique used: " << geneticAlgo->getSelection() << endl;
        cout << "Mutation Technique used: " << geneticAlgo->getMutation() << endl;
        cout << "Crossover Technique used: " << geneticAlgo->getCrossover() << endl;
    } else {
        cout << "--------STATS FOR SIMULATED ANNEALING--------" << endl;
        display();
          //calls display function which actually displays the path
    }

    cout << "Number of Nodes in path: " << graph.size()+1 << endl;
    cout << "Time: " << runTime.count() << endl;
    cout << "Distance: " << lowestDistance << endl;
    cout << "Iterations: " << numIterations << endl << endl;
}

void RunTSP::select(int x) {
    algoExecute = x;
}

void RunTSP::save() {
    ofstream outputFile ("Data/output.txt");

    if (outputFile.is_open()) {
        if(algoExecute == 0) {
            outputFile << "--------STATS FOR NAIVE BRUTE FORCE--------" << endl;
        } else if(algoExecute == 1) {
            outputFile << "--------STATS FOR DYNAMIC PROGRAMMING--------" << endl;
        } else if(algoExecute == 2) {
            outputFile << "--------STATS FOR GENETIC ALGORITHM--------" << endl;
            outputFile << "Selection Technique used: " << geneticAlgo->getSelection() << endl;
            outputFile << "Mutation Technique used: " << geneticAlgo->getMutation() << endl;
            outputFile << "Crossover Technique used: " << geneticAlgo->getCrossover() << endl;

            delete geneticAlgo;
              //deletes geneticAlgo to prevent memory leaks
        } else {
            outputFile << "--------STATS FOR SIMULATED ANNEALING--------" << endl;

            delete simAnnealing;
              //deletes simAnnealing to prevent memory leaks
        }

        outputFile << "Number of Nodes in path: " << graph.size()+1 << endl;
        outputFile << "Time: " << runTime.count() << endl;
        outputFile << "Distance: " << lowestDistance << endl;
        outputFile << "Iterations: " << numIterations << endl << endl;
    } else {
        cout << "Unable to open output file" << endl;
    }

    outputFile.close();
      //closes output file in order to prevent memory leaks
}