//
// Created by reut on 1/23/20.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include <queue>
#include <algorithm>
#include <iostream>
#include <stack>
#include "Searcher.h"

template <class T>
class AStar : public Searcher<T> {
    class Comperator{
    public:
        bool operator()(State<T>* left, State<T>* right) {
            return (left->getF() > right->getF());
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

    // Returns a number of nodes(states) in the path
    int getNumberOfNodes() {
        return this->path.size();
    }

    // Implement of A star algorithm
    vector<State<T>*> search(Searchable<T> *problem) override {
        // Initialize operators
        while (!this->open.empty()) {
            this->open.pop();
        }
        this->closed.clear();
        this->path.clear();

        // Initialization to the initial state
        State<T> *start = problem->getInitialState();
        start->setChangeCost(start->getCost());
        start->setF((problem->calculateHeuristic(start, problem->getGoalState())) + start->getCost());
        this->open.push(problem->getInitialState());

        while (!open.empty()) {
            State<T> *current = this->open.top();
            open.pop();
            this->closed.push_back(current);
            if (problem->isGoalState(current)) {
                backTrace(problem);
                return this->path;
            }
            vector<State<T> *> adjs = problem->getAllPossibleStates(current);
            for (int i = 0; i < adjs.size(); ++i) {
                State<T> *neighbor = adjs[i];
                double tentative_g_score = current->getChangeCost() + neighbor->getCost();
                if (isInClosed(neighbor) || (tentative_g_score >= neighbor->getChangeCost() && neighbor->getChangeCost() != 0)) {
                    continue;
                }
                if (!isInOpen(neighbor) || tentative_g_score < neighbor->getChangeCost() || neighbor->getChangeCost() == 0 ) {
                    neighbor->setCameFromState(current);
                    neighbor->setChangeCost(tentative_g_score);
                    neighbor->setF(neighbor->getChangeCost() + problem->calculateHeuristic(neighbor, problem->getGoalState()));
                    if (!isInOpen(neighbor)) {
                        this->open.push(neighbor);
                    }
                }
            }
        }
        // the case that no path found
        return this->path;
    }
};

#endif //EX4_ASTAR_H
