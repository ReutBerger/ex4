//
// Created by reut on 1/19/20.
//

#include "SearchSolver.h"
#include "Searchable.h"
#include "Matrix.h"
#include "Point.h"
#include "Searcher.h"
#include "BestFS.h"

string SearchSolver::solve(vector<string> problem) {
    string solution;
    //create the problem - searchable
    Searchable<Point> *matrix = new Matrix(problem);
    // check which algorithm is the best
    Searcher<Point> * bestFS = new BestFS<Point>();
    //Searcher<Point> * bFS = new BFS<Point>();
    //Searcher<Point> * dFS = new DFS<Point>();
    //Searcher<Point> * aStar = new Astar<Point>();

    /*TRY*/ cout<< "solution = " << solution <<endl;
    // return the string of ths best solution
    solution = getSolution(bestFS->search(matrix));
    return solution;
}

string SearchSolver::getSolution(vector<State<Point>*> path) {
    string solution = "";
    // State<Point> *fatherX;
    int x, y, fatherX, fatherY;;
    // State<Point> *fatherY;
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
        solution +=  "(" + to_string((int)path[i]->getChangeCost()) + "), ";
    }
    solution = solution.substr(0,solution.length() - 2);
    return solution;
}