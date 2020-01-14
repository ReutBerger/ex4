//
// Created by eden on 12/01/2020.
//

#ifndef EX4_STRINGREVERSE_H
#define EX4_STRINGREVERSE_H

#include <iostream>

#include "Solver.h"

using namespace std;

//template <typename Problem, typename Solution>

class StringReverse : public Solver<string, string> {
public:
    string solve(string problem);
};


#endif //EX4_STRINGREVERSE_H
