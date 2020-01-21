//
// Created by reut on 1/18/20.
//
#ifndef EX4_STATE_H
#define EX4_STATE_H

template <class T>
class State {
private:
    T *state;
    double cost;
    State<T> *came_from;
public:
    State() {}
    State(T *state, double cost) {
        this->state = state;
        this->cost = cost;
        this->came_from = nullptr;
    }

    T* getState() {
        return this->state;
    }

//    Maybe *&state1 ??
    bool operator==(State<T> *state1) {
        return this->state == state1->getState();
    }

    double getCost() {
        return this->cost;
    }

    State<T>* getCameFromState() {
        return this->came_from;
    }

    void setCameFromState(State<T> *state1) {
        this->came_from = state1;
    }

    ~State(){}
};


#endif //EX4_STATE_H
