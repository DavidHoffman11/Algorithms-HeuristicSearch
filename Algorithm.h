#ifndef LAB_4_DYNAMIC_PROGRAMMING_DAVIDHOFFMAN11_ALGORITHM_H
#define LAB_4_DYNAMIC_PROGRAMMING_DAVIDHOFFMAN11_ALGORITHM_H
#include <string>
#include <vector>

using namespace std;

class Algorithm {
public:
    virtual void load() = 0;
    virtual void execute() = 0;
    virtual void display() = 0;
    virtual void stats() = 0;
    virtual void select(int) = 0;
    virtual void save() = 0;
};

#endif //LAB_2_DYNAMIC_PROGRAMMING_DAVIDHOFFMAN11_ALGORITHM_H