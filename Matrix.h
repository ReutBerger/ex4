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
    vector<vector<State<Point>>> matrix;
    State<Point>* startPoint;
    State<Point>* goalPoint;

    vector<string> deleteSpaces(vector<string> vec);

public:
    Matrix(vector<string> problem);
    State<Point>* getInitialState() override;
    State<Point>* getGoalState() override;
    bool isGoalState(State<Point>* state) override ;
    vector<State<Point>*> getAllPossibleStates(State<Point> *s) override;
};


#endif //EX4_MATRIX_H
