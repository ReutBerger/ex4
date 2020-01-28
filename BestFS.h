//
// Created by reut on 1/21/20.
//

#ifndef EX4_BESTFS_H
#define EX4_BESTFS_H

#include <queue>
#include <algorithm>
#include "Searcher.h"

template <class T>
class BestFS : public Searcher<T> {
    class Comperator{
    public:
        bool operator()(State<T>* left, State<T>* right) {
            return (left->getChangeCost() > right->getChangeCost());
        }
    };

private:
    priority_queue<State<T>*, vector<State<T>*>, Comperator> open;
    vector<State<T>*> closed;
    vector<State<T>*> path;

public:
    // Restoring the path we found
    void backTrace(Searchable<T> *problem) {
        State<T>* s = problem->getGoalState();
        this->path.push_back(s);
        while (!s->operator==(problem->getInitialState())) {
            s = s->getCameFromState();
            this->path.push_back(s);
        }
        reverse(this->path.begin(),this->path.end());
    }

    // Checking whether state is in open
    bool isInOpen(State<T>* state) {
        priority_queue<State<T>*, vector<State<T>*>, Comperator> tmp;
        int length = this->open.size();
        State<T>* temp;
        while (!this->open.empty()) {
            temp = this->open.top();
            if (temp->operator==(state)) {
                while (!this->open.empty()) {
                    tmp.push(this->open.top());
                    this->open.pop();
                }
                while (!tmp.empty()) {
                    this->open.push(tmp.top());
                    tmp.pop();
                }
                return true;
            }
            this->open.pop();
            tmp.push(temp);
        }
        while (!tmp.empty()) {
            this->open.push(tmp.top());
            tmp.pop();
        }
        return false;
    }

    // Checking whether state is in closed
    bool isInClosed(State<T>* state) {
        int length = this->closed.size();
        for (int j = 0; j < length; ++j) {
            if (this->closed[j]->operator==(state)) {
                return true;
            }
        }
        return false;
    }

    // Returns the cost of the state in closed
    double costInClosed(State<T>* state) {
        int length = this->closed.size();
        for (int j = 0; j < length; ++j) {
            if (this->closed[j]->operator==(state)) {
                return this->closed[j]->getChangeCost();
            }
        }
        // for compiler
        return 0;
    }

    // Returns the cost of the state in open
    double costInOpen(State<T>* state) {
        priority_queue<State<T>*, vector<State<T>*>, Comperator> tmp;
        int length = this->open.size();
        State<T>* temp;
        while (!this->open.empty()) {
            temp = this->open.top();
            if (temp->operator==(state)) {
                double cost = temp->getChangeCost();
                while (!this->open.empty()) {
                    tmp.push(this->open.top());
                    this->open.pop();
                }
                while (!tmp.empty()) {
                    this->open.push(tmp.top());
                    tmp.pop();
                }
                return cost;
            }
            this->open.pop();
            tmp.push(temp);
        }
        // for compiler
        return 0;
    }

    // Remove this state from closed
    void removeFromClosed(State<T>* state) {
        int length = this->closed.size();
        for (int j = 0; j < length; ++j) {
            if (this->closed[j]->operator==(state)) {
                this->closed.erase(this->closed.begin() + j);
            }
        }
    }

    // Remove this state from open
    priority_queue<State<T>*, vector<State<T>*>, Comperator> removeFromOpen(State<T>* state) {
        priority_queue<State<T>*, vector<State<T>*>, Comperator> tmp;
        State<T>* temp;
        while (!this->open.empty()) {
            temp = this->open.top();
            if (!temp->operator==(state)) {
                tmp.push(temp);
            }
            this->open.pop();
        }
        return tmp;
    }

    // Returns a number of nodes(states) in the path
    int getNumberOfNodes() {
        //not needed
        return this->path.size();
    }

    // Implement of best first search algorithm
    vector<State<T>*> search(Searchable<T> *problem) override {
        State<T>* n;
        // Initialize operators
        while (!this->open.empty()) {
            this->open.pop();
        }
        this->closed.clear();
        this->path.clear();

        // Initialization to the initial state
        problem->getInitialState()->setChangeCost(problem->getInitialState()->getCost());
        this->open.push(problem->getInitialState());
        while (!this->open.empty()) {
            // Remove the best node from OPEN
            n = this->open.top();
            this->open.pop();
            this->closed.push_back(n);
            if (problem->isGoalState(n)) {
                backTrace(problem);
                return this->path;
            }
            vector<State<T>*> adjs = problem->getAllPossibleStates(n);
            int length = adjs.size();
            for (int i = 0; i < length; ++i) {
                if ((!isInOpen(adjs[i])) && (!isInClosed(adjs[i]))) {
                    adjs[i]->setCameFromState(this->closed.back());
                    adjs[i]->setChangeCost(n->getChangeCost() + adjs[i]->getCost());
                    this->open.push(adjs[i]);
                } else {
                    if (isInClosed(adjs[i]) && (adjs[i]->getChangeCost() < costInClosed(adjs[i]))) {
                        adjs[i]->setCameFromState(this->closed.back());
                        adjs[i]->setChangeCost(n->getChangeCost() + adjs[i]->getCost());
                        this->open.push(adjs[i]);
                        removeFromClosed(adjs[i]);
                    } else if (isInOpen(adjs[i]) && (adjs[i]->getChangeCost() < costInOpen(adjs[i]))) {
                        adjs[i]->setCameFromState(this->closed.back());
                        adjs[i]->setChangeCost(n->getChangeCost() + adjs[i]->getCost());
                        this->open = removeFromOpen(adjs[i]);
                        this->open.push(adjs[i]);
                    }
                }
            }
        }
        // the case that no path found
        return this->path;
    }
};

#endif //EX4_BESTFS_H
