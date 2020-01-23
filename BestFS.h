//
// Created by reut on 1/21/20.
//

#ifndef EX4_BESTFS_H
#define EX4_BESTFS_H

#include "Searcher.h"
#include <queue>
#include <algorithm>
#include "iostream"
 using namespace std;

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
        int length = this->open.size();
        State<T>* temp;
        while (!this->open.empty()) {
            temp = this->open.top();
            if (temp->operator==(state)) {
                return true;
            }
            this->open.pop();
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

    double costInOpen(State<T>* state) {
        int length = this->open.size();
        State<T>* temp;
        while (!this->open.empty()) {
            temp = this->open.top();
            if (temp->operator==(state)) {
                return temp->getChangeCost();
            }
            this->open.pop();
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

    int getNumberOfNodes() {
        //not needed
        return this->path.size();
    }

    vector<State<T>*> search(Searchable<T> *problem) override {
        State<T>* n;
        problem->getInitialState()->setChangeCost(problem->getInitialState()->getCost());
        this->open.push(problem->getInitialState());
        while (!this->open.empty()) {
            n = this->open.top();
            this->open.pop();
            this->closed.push_back(n);
            if (problem->isGoalState(n)) {
                backTrace(problem);

//                for (auto i :this->path)
//                cout << "path: (" << i->getState()->getX() << ","<< i->getState()->getY() << ")" << endl;
               return this->path;
            }
            vector<State<T>*> adjs = problem->getAllPossibleStates(n);
            int length = adjs.size();
            for (int i = 0; i < length; ++i) {
                if ((!isInOpen(adjs[i])) && (!isInClosed(adjs[i]))) {
                    adjs[i]->setCameFromState(closed.back());
                    adjs[i]->setChangeCost(n->getChangeCost() + adjs[i]->getCost());
                    this->open.push(adjs[i]);
                } else {
                    if (isInClosed(adjs[i]) && (adjs[i]->getChangeCost() < costInClosed(adjs[i]))) {
                        this->open.push(adjs[i]);
                        removeFromClosed(adjs[i]);
                    } else if (isInOpen(adjs[i]) && (adjs[i]->getChangeCost() < costInOpen(adjs[i]))) {
                        this->open = removeFromOpen(adjs[i]);
                        this->open.push(adjs[i]);
                    }
                }
            }
        }
        int x;
        x =5;
        x +=4;
    }
};


#endif //EX4_BESTFS_H
