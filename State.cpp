//
// Created by reut on 1/18/20.
//

#include "State.h"

template <class T>
State<T>::State(T *state, double cost) {
    this->state = state;
    this->cost = cost;
    this->came_from = nullptr;
}

template <class T>
bool State<T>::operator==(State<T> *state1) {
    return this->state == state1;
}

template <class T>
double State<T>::getCost() {
    return this->cost;
}

template <class T>
State<T> State<T>::getCameFromState() {
    return this->came_from;
}

template <class T>
void State<T>::setCameFromState(State<T> *state1) {
    this->came_from = state1;
}

template <class T>
State<T>::~State() {

}