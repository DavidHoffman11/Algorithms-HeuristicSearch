#include "Algorithm.h"
#include "RunTSP.h"
#include <iostream>

using namespace std;

int main() {
    Algorithm* TSP;
    TSP = new RunTSP();

    for(int i = 0; i < 4; i++) {
        TSP->select(i);
          //selects algo
        TSP->execute();
          //executes selected algo
        TSP->stats();
          //prints stats
        TSP->save();
          //saves stats to output file
    }

    return 0;
}

