//
// Created by reut on 1/23/20.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "Searcher.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <stack>
template <class T>
class AStar : public Searcher<T> {
    class Comperator{
    public:
        bool operator()(State<T>* left, State<T>* right) {
            return (left->getChangeCost() + left->getHeuristic() > right->getChangeCost() + right->getHeuristic());
        }
    };

private:
    priority_queue<State<T>*, vector<State<T>*>, Comperator> open;
    vector<State<T>*> closed;
    vector<State<T>*> path;
public:

    void backTrace(Searchable<T> *problem) {
        State<T>* s = problem->getGoalState();
        this->path.push_back(s);
        while (!s->operator==(problem->getInitialState())) {
            s = s->getCameFromState();
            this->path.push_back(s);
        }
        reverse(this->path.begin(),this->path.end());
    }

    bool isInOpen(State<T>* state) {
        priority_queue<State<T>*, vector<State<T>*>, Comperator> tmp;
        int length = this->open.size();
        State<T>* temp;
        while (!this->open.empty()) {
            temp = this->open.top();
            if (temp->operator==(state)) {
                while (!this->open.empty()) {
                    tmp.push(open.top());
                    open.pop();
                }
                while (!tmp.empty()) {
                    open.push(tmp.top());
                    tmp.pop();
                }
                return true;
            }
            this->open.pop();
            tmp.push(temp);
        }
        while (!tmp.empty()) {
            open.push(tmp.top());
            tmp.pop();
        }
        return false;
    }

    bool isInClosed(State<T>* state) {
        int length = this->closed.size();
        for (int j = 0; j < length; ++j) {
            if (this->closed[j]->operator==(state)) {
                return true;
            }
        }
        return false;
    }
/*
    double costInClosed(State<T>* state) {
        int length = this->closed.size();
        for (int j = 0; j < length; ++j) {
            if (this->closed[j]->operator==(state)) {
                return this->closed[j]->getChangeCost() + this->closed[j]->getHeuristic();
            }
        }
        // for compiler
        return 0;
    }

    double costInOpen(State<T>* state) {
        priority_queue<State<T>*, vector<State<T>*>, Comperator> tmp;
        int length = this->open.size();
        State<T>* temp;
        while (!this->open.empty()) {
            temp = this->open.top();
            if (temp->operator==(state)) {
                double cost = temp->getChangeCost() + temp->getHeuristic();
                while (!this->open.empty()) {
                    tmp.push(this->open.top());
                    open.pop();
                }
                while (!tmp.empty()) {
                    open.push(tmp.top());
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

    void removeFromClosed(State<T>* state) {
        int length = this->closed.size();
        for (int j = 0; j < length; ++j) {
            if (this->closed[j]->operator==(state)) {
                this->closed.erase(this->closed.begin() + j);
            }
        }
    }

   priority_queue<State<T>*, vector<State<T>*>, Comperator> removeFromOpen(State<T>* state) {
        priority_queue<State<T> *, vector<State<T> *>, Comperator> tmp;
        State<T> *temp;
        while (!this->open.empty()) {
            temp = this->open.top();
            if (!temp->operator==(state)) {
                tmp.push(temp);
            }
            this->open.pop();
        }
        return tmp;
    }
*/
    int getNumberOfNodes() {
        return this->path.size();
    }


    vector<State<T>*> search(Searchable<T> *problem) override {
        // initialization to the initial state
        problem->getInitialState()->setChangeCost(problem->getInitialState()->getCost());
        problem->getInitialState()->setHeuristic
                       (problem->calculateHeuristic(problem->getInitialState(),problem->getGoalState()));
        this->open.push(problem->getInitialState());

        while (!open.empty()) {
            State<T>* current = open.top();
            open.pop();
            this->closed.push_back(current);
            if (problem->isGoalState(current)) {
                backTrace(problem);
               return this->path;
            }
            vector<State<T>*> adjs = problem->getAllPossibleStates(current);
            for (int i = 0; i < adjs.size(); ++i) {
                double cost;
                if ((!isInOpen(adjs[i])) && (!isInClosed(adjs[i]))) {
                    adjs[i]->setCameFromState(current);
                    adjs[i]->setChangeCost(current->getChangeCost() + adjs[i]->getCost());
                    cost = problem->calculateHeuristic(adjs[i], problem->getGoalState());
                    adjs[i]->setHeuristic(cost);
                    this->open.push(adjs[i]);
                } else if (isInOpen(adjs[i]) && (adjs[i]->getChangeCost() > current->getChangeCost() + adjs[i]->getCost())) {
                    //removeFromOpen(adjs[i]);
                    stack<State<T>*> tempStack;
                    while (open.top() != adjs[i]) {
                        tempStack.push(open.top());
                        open.pop();
                    }
                    State<T>* temp = open.top();
                    open.pop();
                    temp->setChangeCost(current->getChangeCost() + adjs[i]->getCost());
                    temp->setCameFromState(current);
                    cost = problem->calculateHeuristic(adjs[i], problem->getGoalState());
                    temp->setHeuristic(cost);
                    open.push(temp);
                    while (!tempStack.empty()) {
                        open.push(tempStack.top());
                        tempStack.pop();
                    }
                }
            }
//             Wiki
//            tentative_g_score := g_score[current] + dist_between(current,neighbor)
//            if neighbor in closedset or tentative_g_score >= g_score[neighbor]
//            continue
//            if neighbor not in openset or tentative_g_score < g_score[neighbor]
//            came_from[neighbor] := current
//            g_score[neighbor] := tentative_g_score
//            f_score[neighbor] := g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)
//            if neighbor not in openset
//            add neighbor to openset

        }
        return this->path;


//        State<T>* n;
//        problem->getInitialState()->setChangeCost(problem->getInitialState()->getCost());
//        problem->getInitialState()->setHeuristic(problem->calculateHeuristic
//                                    (problem->getInitialState(), problem->getGoalState()));
//        this->open.push(problem->getInitialState());
//        while (!this->open.empty()) {
//            n = this->open.top();
//            this->open.pop();
//            this->closed.push_back(n);
//            if (problem->isGoalState(n)) {
//                backTrace(problem);
//                return this->path;
//            }
//            vector<State<T>*> adjs = problem->getAllPossibleStates(n);
//             ////////// the same as bestfs
//            for (int k = 0; k < adjs.size(); k++) {
//                adjs[k]->setHeuristic(problem->calculateHeuristic(adjs[k], problem->getGoalState()));
//            }
//            find:
//            int index = 0;
//            if (adjs.size()) {
//                double min = adjs[0]->getCost() + adjs[0]->getHeuristic();
//                for (int j = 1; j < adjs.size(); ++j) {
//                    if (min > adjs[j]->getCost() + adjs[j]->getHeuristic()) {
//                        min = adjs[j]->getCost() + adjs[j]->getHeuristic();
//                        index = j;
//                    }
//                }
//                /////////////////////////////////////////////////////////////////////
//                if ((!isInOpen(adjs[index])) && (!isInClosed(adjs[index]))) {
//                    adjs[index]->setCameFromState(closed.back());
//                    adjs[index]->setChangeCost(n->getChangeCost() + adjs[index]->getCost());
//                    open.push(adjs[index]);
//                    adjs.erase(adjs.begin()+index);
//                    //////////////////////////////////////////////////////////////////
//                    } else {
//                        adjs.erase(adjs.begin()+index);
//                        goto find;
//                    }
//                }
//                for (int i = 0; i < adjs.size(); ++i) {
//
//                    if ((!isInOpen(adjs[i])) && (!isInClosed(adjs[i]))) {
//                        adjs[i]->setCameFromState(closed.back());
//                        adjs[i]->setChangeCost(n->getChangeCost() + adjs[i]->getCost());
//                        this->open.push(adjs[i]);
//                    } else {
//                        if (isInClosed(adjs[i]) && (adjs[i]->getChangeCost() < costInClosed(adjs[i]))) {
//                            adjs[i]->setCameFromState(closed.back());
//                            adjs[i]->setChangeCost(n->getChangeCost() + adjs[i]->getCost());
//                            this->open.push(adjs[i]);
//                            removeFromClosed(adjs[i]);
//                        } else if (isInOpen(adjs[i]) && (adjs[i]->getChangeCost() < costInOpen(adjs[i]))) {
//                            adjs[i]->setCameFromState(closed.back());
//                            adjs[i]->setChangeCost(n->getChangeCost() + adjs[i]->getCost());
//                            this->open = removeFromOpen(adjs[i]);
//                            this->open.push(adjs[i]);
//                        }
//                    }
//                }
//        }
    }
};



#endif //EX4_ASTAR_H
