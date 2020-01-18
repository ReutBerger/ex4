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
    State<T> getInitialState();
//    Maybe State<T> instead bool ??
    bool getGoalState();
    vector<State<T>> getAllPossibleStates(State<T> s);
};


#endif //EX4_SEARCHABLE_H
