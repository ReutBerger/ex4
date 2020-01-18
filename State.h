//
// Created by reut on 1/18/20.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

template <class T>
class State {
private:
    T state;
    double cost;
    State<T> *came_from;
public:
    State<T>(T state);
//    Maybe *&state1 ??
    bool operator==(State<T> *state1);
    ~State();
};


#endif //EX4_STATE_H
