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
    int numOfVisitedNodes = 0;
    double PathCost;

public:
    // Constructor
    DFS() {

    }

    vector<State<T>*> search(Searchable<T>* searchable) override {
        // Initialize operators
        State<T>* initialState = searchable->getInitialState();
        stateStack.push(initialState);
        visitedNodes.push_back(initialState);

        // Go over all state stack until you get to the goal state, and return the path
        while (!stateStack.empty()) {
            // Dequeue a state from queue
            State<T> *currentState = stateStack.top();
            stateStack.pop();

            // Update the number of node we visited in this problem by 1.
            this->numOfVisitedNodes += 1;

            // If we got to the goal state, return the path
            if (searchable->getGoalState()->operator==(currentState)) {
                // Update the path Cost
                this->PathCost += currentState->getCost();
                path.insert(path.begin(), currentState);

                while (!currentState->operator==(initialState)) {
                    // In order to find the path, get the previous state
                    currentState = currentState->getCameFromState();

                    // Update the path Cost
                    this->PathCost += currentState->getCost();
                    path.insert(path.begin(), currentState);
                }
                return path;
            } else {
                // Check if we visited the current state neighbors
                for (State<T> *adj : searchable->getAllPossibleStates(currentState)) {
                    // Adjacent has not been visited before
                    bool visited = false;
                    for(State<T>* s : visitedNodes) {
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
                        visitedNodes.push_back(adj);
                        stateStack.push(adj);
                    }
                }
            }
        }
        // TODO: IF PATH NOT FOUND, WHAT SHOULD I RETURN?
    }

    int getNumberOfNodes() override {
        return this->path.size();
    }
};


#endif //EX4_DFS_H
