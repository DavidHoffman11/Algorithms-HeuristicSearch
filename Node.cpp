#include "Node.h"
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

Node::Node(int x){
    data = x;
    isVisited = false;
}

Node::Node(int val, int x, int y, int z){
    data = val;
    isVisited = false;
    position.push_back(x);
    position.push_back(y);
    position.push_back(z);
}

void Node::setData(int x){
    data = x;
}

int Node::getData(){
    return data;
}

void Node::setVisit(bool x) {
    isVisited = x;
}

bool Node::getVisit() {
    return isVisited;
}

void Node::setPosition(int x, int y, int z){
    position.push_back(x);
    position.push_back(y);
    position.push_back(z);
}

vector<int>& Node::getPosition(){
    return this->position;
}

void Node::setWeight(int dest, double weight) {
/*
    for(int i = 0; i < connectedNodes.size(); i++) {
        if(connectedNodes[i].first.getData() == dest) {
            connectedNodes[i].second = weight;
        }
    }
*/
}

double Node::getWeight(Node n) {
/*
    for(int i = 0; i < connectedNodes.size(); i++) {
        if(connectedNodes[i].first == n) {
            return connectedNodes[i].second;
        }
    }
*/
    return 0;
}

vector<double> Node::getWeights() {
    vector <double> weights;
/*
    for(int i = 0; i < connectedNodes.size(); i++) {
        weights.push_back(connectedNodes[i].second);
    }
*/
    return weights;
}

void Node::setConnections(Node x) {
    connectedNodes.push_back(x);
}

vector<Node> Node::getConnections() {
    return connectedNodes;
}

int Node::size(){
    return connectedNodes.size();
}

bool Node::operator== (const Node &x) const{
    return (this->data == x.data);
}

bool Node::operator!= (const Node &x) const{
    return (this->data != x.data);
}

Node& Node::operator[] (const int x){
    return connectedNodes[x];
}

bool Node::operator> (const Node &x) const{
    return (this->data > x.data);
}

bool Node::operator< (const Node &x) const{
    return (this->data < x.data);
}

bool Node::operator>= (const Node &x) const{
    return (this->data >= x.data);
}

bool Node::operator<= (const Node &x) const{
    return (this->data <= x.data);
}

Node& Node::operator= (const Node &x) {
    if (this != &x) {
        data = x.data;
        position = x.position;
        connectedNodes = x.connectedNodes;
    }

    return *this;
}