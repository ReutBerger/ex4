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

//template <class T>

class SearchSolver : public Solver<vector<string>, string> {
public:
//    SearchSolver(Searcher<T> *searcher) {
//        mSearcher = searcher;
//    }

    string solve(vector<string> problem);
    string getSolution(vector<State<Point>*> path);
// TODO - implement.

};


#endif //EX4_SEARCHSOLVER_H
