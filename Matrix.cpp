//
// Created by reut on 1/19/20.
//

#include "Matrix.h"
#include <iostream>

// Constructor- build the matrix and update members
Matrix::Matrix(vector<string> problem) {
    // Create Matrix
    vector<vector<State<Point>>> matrix;
    vector<State<Point>> lineVec;
    int i = 0, j = 0, count = 0;
    string line, temp_num = "";
    while (j < problem.size() - 3) {
        line = problem[j];
        while (line[count] != '\0') {
            temp_num += line[count];
            if (line[count] == ',') {
                temp_num = temp_num.substr(0,count);
                // Create new state
                State<Point>* s = new State<Point>(new Point(i,j), stod(temp_num));
                lineVec.push_back(*s);
                /*TRY*/ cout << temp_num <<i << j << endl;
                i++;
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
        i = 0;
        j++;
        matrix.push_back(lineVec);
    }
    // Initialize members
    this->matrix = matrix;
    string temp = problem[problem.size() - 3];
    i = (int)temp[0] - '0';
    j = (int)temp[2] - '0';
    this->startPoint = matrix[i][j];
    temp = problem[problem.size() - 2];
    i = (int)temp[0] - '0';
    j = (int)temp[2] - '0';
    this->goalPoint = matrix[i][j];
}

State<Point> Matrix::getInitialState() {
    return this->startPoint;
}

State<Point> Matrix::getGoalState() {
    return this->goalPoint;
}

vector<State<Point>> Matrix::getAllPossibleStates(State<Point> s) {
    vector<State<Point>> adj_vec;
    int x = s.getState()->getX();
    int y = s.getState()->getY();
    int row_size = this->matrix.front().size();

    // Check state up limit
    if (y != 0) {
        adj_vec.push_back(this->matrix[x][y - 1]);
    }
    // Check state left limit
    if (x != 0) {
        adj_vec.push_back(this->matrix[x - 1][y]);
    }
    // Check state down limit
    if (y != row_size - 1) {
        adj_vec.push_back(this->matrix[x][y + 1]);
    }
    // Check state right limit
    if (x != row_size - 1) {
        adj_vec.push_back(this->matrix[x + 1][y]);
    }

    return adj_vec;
}


//TODO - delete - example Matrix
// vector<string> vec = {"1,2,3","4,5,6","7,8,9","0,0","2,2","end"};