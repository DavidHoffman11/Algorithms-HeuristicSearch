#ifndef LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_NODE_H
#define LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_NODE_H
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

class Node {
public:
    Node() {};
    Node(int);
    Node(int, int, int, int);
    void setData(int);
    int getData();
    void setVisit(bool);
    bool getVisit();
    void setPosition(int, int, int);
    vector<int>& getPosition();
    void setWeight(int, double);
    double getWeight(Node);
    vector<double> getWeights();
    void setConnections(Node);
    vector<Node> getConnections();
    int size();
    //overloaded operators
    bool operator== (const Node&) const;
    bool operator!= (const Node&) const;
    Node& operator[] (const int);
    bool operator> (const Node&) const;
    bool operator<= (const Node&) const;
    bool operator< (const Node&) const;
    bool operator>= (const Node&) const;
    Node& operator= (const Node&);

private:
    int data;
    bool isVisited;
    vector<Node> connectedNodes;
    vector<int> position;
};


#endif //LAB_4_HEURISTIC_SEARCH_DAVIDHOFFMAN11_NODE_H
