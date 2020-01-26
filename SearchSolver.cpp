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

string SearchSolver::solve(vector<string> problem) {
    string solution;
    //create the problem - searchable
    Searchable<Point> *matrix = new Matrix(problem);
    // check which algorithm is the best
    /*TRY*///Searcher<Point> * bestFS = new BestFS<Point>();
    /*TRY*///Searcher<Point> * bFS = new BFS<Point>();
    /*TRY*///Searcher<Point> * dFS = new DFS<Point>();
   /*TRY*/// Searcher<Point> * aStar = new AStar<Point>();

    /*TRY*/ cout<< "solution = " << solution;
    // return the string of ths best solution
    solution = getSolution(this->mSearcher->search(matrix));
    return solution;
}

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