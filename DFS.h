//
// Created by eden on 23/01/2020.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H

#include <iostream>
#include <list>
#include <stack>

#include "Searcher.h"
#include "State.h"

using namespace std;

template <class T>

class DFS : public Searcher<T> {
private:
    stack<State<T>* > stateStack;
    vector<State<T>*> visitedNodes;
    vector<State<T>*> path;
    double totalCost = 0;

public:
    // Constructor
    DFS() {}

    // Implement of DFS algorithm
    vector<State<T>*> search(Searchable<T>* searchable) override {
        // Initialize operators
        while (!this->stateStack.empty()) {
            this->stateStack.pop();
        }
        this->path.clear();
        this->visitedNodes.clear();
        totalCost = 0;

        State<T>* initialState = searchable->getInitialState();
        this->stateStack.push(initialState);
        this->visitedNodes.push_back(initialState);

        // Go over all state stack until you get to the goal state, and return the path
        while (!this->stateStack.empty()) {
            // Dequeue a state from queue
            State<T> *currentState = this->stateStack.top();
            this->stateStack.pop();

            // If we got to the goal state, return the path
            if (searchable->getGoalState()->operator==(currentState)) {
                this->path.insert(this->path.begin(), currentState);

                while (!currentState->operator==(initialState)) {
                    // In order to find the path, get the previous state
                    currentState = currentState->getCameFromState();

                    this->path.insert(this->path.begin(), currentState);
                }
                // Update the path Cost
                for (State<T>* s : this->path) {
                    this->totalCost += s->getCost();
                    s->setChangeCost(this->totalCost);
                }
                return this->path;
            } else {
                // Check if we visited the current state neighbors
                for (State<T> *adj : searchable->getAllPossibleStates(currentState)) {
                    // Adjacent has not been visited before
                    bool visited = false;
                    for(State<T>* s : this->visitedNodes) {
                        if (s->operator==(adj)) {
                            visited = true;
                            break;
                        }
                    }
                    if (visited) {
                        continue;
                    }
                    else {
                        // Mark the current node dad as the current node
                        adj->setCameFromState(currentState);
                        this->visitedNodes.push_back(adj);
                        this->stateStack.push(adj);
                    }
                }
            }
        }
        // The case that no path found
        return this->path;
    }

    // Returns a number of nodes(states) in the path
    int getNumberOfNodes() override {
        return this->path.size();
    }
};

#endif //EX4_DFS_H
