//
// Created by eden on 19/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include <iostream>
#include <list>
#include <queue>

#include "Searcher.h"
#include "State.h"

using namespace std;

template <class T>

class BFS : public Searcher<T> {
private:
    queue<State<T> *> nodesQueue;
    vector<State<T>*> visitedNodes;
    vector<State<T>*> path;
    double totalCost = 0;

public:
    // Constructor
    BFS() {

    }

    vector<State<T>*> search(Searchable<T>* searchable) override {
        // Initialize operators
        State<T>* initialState = searchable->getInitialState();
        nodesQueue.push(initialState);
        visitedNodes.push_back(initialState);

        // Go over all state queue until you get to the goal state, and return the path
        while (!nodesQueue.empty()) {
            // Dequeue a state from queue
            State<T> *currentState = nodesQueue.front();
            nodesQueue.pop();

            // If we got to the goal state, return the path
            if (searchable->getGoalState()->operator==(currentState)) {
                path.insert(path.begin(), currentState);

                while (!currentState->operator==(initialState)) {
                    // In order to find the path, get the previous state
                    currentState = currentState->getCameFromState();
                    path.insert(path.begin(), currentState);
                }
                // Update the path Cost
                for (State<T>* s : path) {
                    totalCost += s->getCost();
                    s->setChangeCost(totalCost);
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
                        nodesQueue.push(adj);
                    }
                }
            }
        }
        // The case that no path found
        return this->path;
    }

    int getNumberOfNodes() override {
        return this->path.size();
    }
};


#endif //EX4_BFS_H
