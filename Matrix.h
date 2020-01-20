//
// Created by reut on 1/19/20.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H

#include <vector>
#include <string>
#include "Searchable.h"
#include "Point.h"

class Matrix : public Searchable<Point>{
private:
//     vector<vector<State<Point>>> matrix;
     State<Point> startPoint;
     State<Point> goalPoint;
public:
    vector<vector<State<Point>>> matrix;
    Matrix(vector<string> problem);
    State<Point> getInitialState() override;
    State<Point> getGoalState() override;
//    bool isGoalState(State<Point> s);
    vector<State<Point>> getAllPossibleStates(State<Point> s);
};


#endif //EX4_MATRIX_H
