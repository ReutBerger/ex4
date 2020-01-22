//
// Created by reut on 1/18/20.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "Searchable.h"
#include <string>

template <typename T>
class Searcher {
public:
    virtual vector<State<T>*> search(Searchable<T>* problem) = 0;
    virtual int getNumberOfNodes() = 0;
};

#endif //EX4_SEARCHER_H
