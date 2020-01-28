//
// Created by reut on 1/19/20.
//

#include "SearchSolver.h"
#include "Searchable.h"
#include "Matrix.h"
#include "Point.h"
#include "Searcher.h"
#include "BestFS.h"
#include "AStar.h"

SearchSolver::SearchSolver(Searcher<Point> *searcher) {
    this->mSearcher = searcher;
}

string SearchSolver::solve(vector<string> problem) {
    //create the problem - searchable
    Searchable<Point> *matrix = new Matrix(problem);

    // return the string of the solution
    string solution = getSolution(this->mSearcher->search(matrix));

    delete matrix;

    return solution;
}

// Return the string of the path
string SearchSolver::getSolution(vector<State<Point>*> path) {
    string solution;
    solution = "";
    int x, y, fatherX, fatherY;;
    if(path.empty()){
        return "No Solution found";
    } else {
        for (int i = 1; i < path.size(); ++i) {
            x = path[i]->getState()->getX();
            y = path[i]->getState()->getY();
            fatherX = path[i]->getCameFromState()->getState()->getX();
            fatherY = path[i]->getCameFromState()->getState()->getY();
            if (y == fatherY && (x - 1 == fatherX)) {
                solution += "Down ";
            } else if (y == fatherY && (x + 1 == fatherX)) {
                solution += "Up ";
            } else if (x == fatherX && (y - 1 == fatherY)) {
                solution += "Right ";
            } else if (x == fatherX && (y + 1 == fatherY)) {
                solution += "Left ";
            } else {
                continue;
            }
            solution += "(" + to_string((int) path[i]->getChangeCost()) + "), ";
        }
        solution = solution.substr(0, solution.length() - 2);
        return solution;
    }
}
