//
// Created by reut on 1/19/20.
//

#include "Matrix.h"
#include <iostream>

// Constructor- build the matrix and update members
Matrix::Matrix(vector<string> problem) {
    vector<State<Point>> lineVec;
    int i = 0, j = 0, count = 0;
    string line, temp_num = "";

    while (i < problem.size() - 3) {
        line = problem[i];
        while (line[count] != '\0') {
            temp_num += line[count];
            if (line[count] == ',') {
                temp_num = temp_num.substr(0,count);
                // Create new state
                State<Point>* s = new State<Point>(new Point(i,j), stod(temp_num));
                lineVec.push_back(*s);
                /*TRY*/ cout << temp_num <<i << j << endl;
                j++;
                line.erase(0, count + 1);
                temp_num = "";
                count = -1;
            }
            count++;
        }
        if(temp_num != "") {
            // Create new state
            State<Point>* s = new State<Point>(new Point(i,j), stod(temp_num));
            lineVec.push_back(*s);
            /*TRY*/ cout << temp_num << i << j << endl;
            temp_num = "";
        }
        count = 0;
        j = 0;
        i++;
        matrix.push_back(lineVec);
        lineVec.clear();
    }

    // Initialize members
    sscanf(problem[problem.size() - 3].c_str(), "%d,%d", &i, &j);
    this->startPoint = &matrix[i][j];

    sscanf(problem[problem.size() - 2].c_str(), "%d,%d", &i, &j);
    this->goalPoint = &matrix[i][j];
}

State<Point>* Matrix::getInitialState() {
    return this->startPoint;
}

State<Point>* Matrix::getGoalState() {
    return this->goalPoint;
}

vector<State<Point>*> Matrix::getAllPossibleStates(State<Point> *s) {
    vector<State<Point>*> adj_vec;
    int x = s->getState()->getX();
    int y = s->getState()->getY();
    int row_size = this->matrix.front().size();

    // Check state up limit
    if (y != 0 && (this->matrix[x][y - 1].getCost() != -1)) {
        adj_vec.push_back(&this->matrix[x][y - 1]);
    }
    // Check state left limit
    if (x != 0 && (this->matrix[x - 1][y].getCost() != -1)) {
        adj_vec.push_back(&this->matrix[x - 1][y]);
    }
    // Check state down limit
    if (y != row_size - 1 && (this->matrix[x][y + 1].getCost() != -1)) {
        adj_vec.push_back(&this->matrix[x][y + 1]);
    }
    // Check state right limit
    if (x != row_size - 1 && (this->matrix[x + 1][y].getCost() != -1)) {
        adj_vec.push_back(&this->matrix[x + 1][y]);
    }

    return adj_vec;
}
