//
// Created by reut on 1/19/20.
//

#ifndef EX4_SEARCHSOLVER_H
#define EX4_SEARCHSOLVER_H

#include "Solver.h"
#include <string>
#include <vector>

using namespace std;

class SearchSolver : public Solver<vector<string>, string> {
public:
    string solve(vector<string> problem);
};


#endif //EX4_SEARCHSOLVER_H
