//
// Created by reut on 1/19/20.
//

#ifndef EX4_SEARCHSOLVER_H
#define EX4_SEARCHSOLVER_H

#include "Solver.h"
#include <string>
#include <vector>
#include "State.h"
#include "Point.h"

using namespace std;

class SearchSolver : public Solver<vector<string>, string> {
private:

public:
    string solve(vector<string> problem);
    string getSolution(vector<State<Point>*> path);

};


#endif //EX4_SEARCHSOLVER_H
