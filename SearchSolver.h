//
// Created by reut on 1/19/20.
//

#ifndef EX4_SEARCHSOLVER_H
#define EX4_SEARCHSOLVER_H

#include <string>
#include <vector>

#include "Solver.h"
#include "Searcher.h"
#include "Matrix.h"
#include "Point.h"

using namespace std;

class SearchSolver : public Solver<vector<string>, string> {
private:
    Searcher<Point> *mSearcher;
public:
    SearchSolver(Searcher<Point> *searcher);
    string solve(vector<string> problem) override;
    string getSolution(vector<State<Point>*> path);
};

#endif //EX4_SEARCHSOLVER_H
