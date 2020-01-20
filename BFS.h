//
// Created by eden on 19/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include<iostream>
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
    int numOfVisitedNodes = 0;
    double PathCost;

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

            // Update the number of node we visited in this problem by 1.
            this->numOfVisitedNodes += 1;

            // If we got to the goal state, return the path
            if (searchable->isGoalState(currentState)) {
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
                    if (find(visitedNodes.begin(), visitedNodes.end(), adj) != visitedNodes.end()) {
                        // Mark the current node dad as the current node
                        adj->setCameFromState(currentState);
                        visitedNodes.push_back(adj);
//                        visitedNodes.emplace_back(adj);
                        nodesQueue.push(adj);
                    }
                }
            }
        }
        // TODO: IF PATH NOT FOUND, WHAT SHOULD I RETURN?
    }
};


#endif //EX4_BFS_H
