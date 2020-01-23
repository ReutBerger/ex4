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

template <class T>

class SearchSolver : public Solver<vector<string>, string> {
public:
    SearchSolver(Searcher<T> *searcher) {
        mSearcher = searcher;
    }

    string solve(vector<string> problem) {
        string solution;
        Searchable<Point> *matrix = new Matrix(problem);

//        ??? = mSearcher->search(matrix);
// TODO - implement.

solution = "abc";
        return solution;
    }

private:
    Searcher<T> *mSearcher;
};


#endif //EX4_SEARCHSOLVER_H
