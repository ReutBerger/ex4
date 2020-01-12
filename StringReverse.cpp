//
// Created by eden on 12/01/2020.
//

#include "StringReverse.h"

#include <algorithm>

string StringReverse::Solve(string problem) {
    reverse(problem.begin(), problem.end());
    return problem;
}