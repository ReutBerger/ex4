//
// Created by reut on 1/12/20.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

template <typename Problem, typename Solution>

class Solver{
public:
    virtual Solution solve(Problem problem) = 0;
};
#endif //EX4_SOLVER_H
