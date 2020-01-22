//
// Created by reut on 1/21/20.
//

#ifndef EX4_BESTFS_H
#define EX4_BESTFS_H

#include "Searcher.h"
#include <deque>
#include <vector>
 using namespace std;
template <class T>
class BestFS : public Searcher<T> {
public:
    vector<State<T>*> search(Searchable<T> *problem) override {
//        string solution;
//        deque<State <T>> open {};
//        open.push_back(problem->getInitialState());
//        vector<State<T>> closed {};
//        while(open.size() > 0) {
//            State<T> n = open.front();
//            open.pop_front();
//            closed.push_back(n);
           // if(n == problem->getGoalState()){
                //backtrace path to n and return the path;
            //}
//            vector<State<T>> adjs = problem->getAllPossibleStates();
//            for(auto it : adjs) {
//                if(find(closed.begin(), open.begin() ,it) != closed.end()){
//
//                }
//            }




        }


//        return solution;

};


#endif //EX4_BESTFS_H
