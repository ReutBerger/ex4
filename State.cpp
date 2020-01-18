//
// Created by reut on 1/18/20.
//

#include "State.h"

template <class T>
State<T>::State(T state) {
    this->state = state;
}

template <class T>
bool State<T>::operator==(State<T> *state1) {
    return this->state == state1;
}

template <class T>
State<T>::~State() {

}