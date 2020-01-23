//
// Created by reut on 1/21/20.
//

#ifndef EX4_BESTFS_H
#define EX4_BESTFS_H

#include "Searcher.h"
#include <queue>
#include <algorithm>

 using namespace std;

template <class T>
class BestFS : public Searcher<T> {
    class Comperator{
    public:
        bool operator()(State<T>* left, State<T>* right) {
            return (left->getChangeCost() > right->getChangeCost());
        }
    };

public:
    vector<State<T>*> backTrace(Searchable<T> *problem, vector<State<T>*> closed) {
        vector<State<T>*> path;
        State<T>* s = problem->getGoalState();
        path.push_back(s);
        while (!s->operator==(problem->getInitialState())) {
            s = s->getCameFromState();
            path.push_back(s);
        }
        reverse(path.begin(),path.end());
        return path;
    }
    bool isInOpen(priority_queue<State<T>*, vector<State<T>*>, Comperator> open, State<T>* state) {
        int length = open.size();
        State<T>* temp;
        while (!open.empty()) {
            temp = open.top();
            if (temp->operator==(state)) {
                return true;
            }
            open.pop();
        }
        return false;
    }
    bool isInClosed(vector<State<T>*> closed, State<T>* state) {
        int length = closed.size();
        for (int j = 0; j < length; ++j) {
            if (closed[j]->operator==(state)) {
                return true;
            }
        }
        return false;
    }
    double costInClosed(vector<State<T>*> closed, State<T>* state) {
        int length = closed.size();
        for (int j = 0; j < length; ++j) {
            if (closed[j]->operator==(state)) {
                return closed[j]->getChangeCost();
            }
        }
        // for compiler
        return 0;
    }
    double costInOpen(priority_queue<State<T>*, vector<State<T>*>, Comperator> open, State<T>* state) {
        int length = open.size();
        State<T>* temp;
        while (!open.empty()) {
            temp = open.top();
            if (temp->operator==(state)) {
                return temp->getChangeCost();
            }
            open.pop();
        }
        // for compiler
        return 0;
    }
    vector<State<T>*> removeFromClosed(vector<State<T>*> closed, State<T>* state) {
        int length = closed.size();
        for (int j = 0; j < length; ++j) {
            if (closed[j]->operator==(state)) {
                closed.erase(closed.begin() + j);
            }
        }
        return closed;
    }
    priority_queue<State<T>*, vector<State<T>*>, Comperator> removeFromOpen
                        (priority_queue<State<T>*, vector<State<T>*>, Comperator> open, State<T>* state) {
        priority_queue<State<T>*, vector<State<T>*>, Comperator> tmp;
        State<T>* temp;
        while (!open.empty()) {
            temp = open.top();
            if (!temp->operator==(state)) {
                tmp.push(temp);
            }
            open.pop();
        }
        return tmp;
    }

    int getNumberOfNodes() {
        //not needed
        return 0;
    }

    vector<State<T>*> search(Searchable<T> *problem) override {
        State<T>* n;
        priority_queue<State<T>*, vector<State<T>*>, Comperator> open;
        vector<State<T>*> closed;
        problem->getInitialState()->setChangeCost(problem->getInitialState()->getCost());
        open.push(problem->getInitialState());
        while (!open.empty()) {
            n = open.top();
            open.pop();
            closed.push_back(n);
            if (problem->isGoalState(n)) {
               return backTrace(problem, closed);
            }
            vector<State<T>*> adjs = problem->getAllPossibleStates(n);
            int length = adjs.size();
            for (int i = 0; i < length; ++i) {
                if ((!isInOpen(open,adjs[i])) && (!isInClosed(closed, adjs[i]))) {
                    adjs[i]->setCameFromState(n);
                    adjs[i]->setChangeCost(n->getChangeCost() + adjs[i]->getCost());
                    open.push(adjs[i]);
                } else {
                    if (isInClosed(closed, adjs[i]) && (adjs[i]->getChangeCost() < costInClosed(closed, adjs[i]))) {
                        open.push(adjs[i]);
                        closed = removeFromClosed(closed, adjs[i]);
                    } else if (isInOpen(open, adjs[i]) && (adjs[i]->getChangeCost() < costInOpen(open, adjs[i]))) {
                        open = removeFromOpen(open, adjs[i]);
                        open.push(adjs[i]);
                    }
                }
            }

        }
    }
};


#endif //EX4_BESTFS_H
