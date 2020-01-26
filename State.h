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
    double change_cost;
    double f;
    State<T> *came_from;
public:
    State() {}
    State(T *state, double cost) {
        this->state = state;
        this->cost = cost;
        this->change_cost = 0;
        this->came_from = nullptr;
        this->f = 0;
    }

    T* getState() {
        return this->state;
    }

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

    void setChangeCost(double changeCost) {
        this->change_cost = changeCost;
    }

    double getChangeCost() {
        return this->change_cost;
    }

    void setF(double heuristic1) {
        this->f = heuristic1;
    }

    double getF() {
        return this->f;
    }

    ~State(){}
};


#endif //EX4_STATE_H
