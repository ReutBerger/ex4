//
// Created by reut on 1/18/20.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include <vector>
#include "State.h"
using namespace std;

template <class T>
class Searchable {
public:
    virtual State<T> getInitialState() = 0;
    virtual State<T> getGoalState() = 0;
    virtual bool isGoalState() = 0;
    virtual vector<State<T>> getAllPossibleStates(State<T> s) = 0;
};


#endif //EX4_SEARCHABLE_H
