//
// Created by reut on 1/12/20.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

template <typename Problem, typename Solution>

class Solver{
    virtual Solution Solve(Problem problem) = 0;
};
#endif //EX4_SOLVER_H
