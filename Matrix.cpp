//
// Created by reut on 1/19/20.
//

#include "Matrix.h"

// Constructor- build the matrix and update members
Matrix::Matrix(vector<string> problem1) {
    // Delete all spaces in the given problem
    vector<string> problem = deleteSpaces(problem1);

    vector<State<Point>> lineVec;
    int i = 0, j = 0, index = 0, counter = 0;
    string line, temp_num = "";

    // Initializes the length of the matrix rows
    this->row = problem.size() - 3;

    // Initializes the length of the matrix cols
    for (int k = 0; k < problem[0].size(); ++k) {
        if (problem[0][k] == ',') {
               counter++;
        }
    }
    counter++;
    this->col = counter;

    while (i < this->row) {
        line = problem[i];
        while (line[index] != '\0') {
            temp_num += line[index];
            if (line[index] == ',') {
                temp_num = temp_num.substr(0, index);
                // Create new state
                State<Point>* s = new State<Point>(new Point(i,j), stod(temp_num));
                lineVec.push_back(*s);
                j++;
                line.erase(0, index + 1);
                temp_num = "";
                index = -1;
            }
            index++;
        }
        if(temp_num != "") {
            // Create new state
            State<Point>* s = new State<Point>(new Point(i,j), stod(temp_num));
            lineVec.push_back(*s);
            temp_num = "";
        }
        index = 0;
        j = 0;
        i++;
        this->matrix.push_back(lineVec);
        lineVec.clear();
    }

    // Initializes the initial point
    sscanf(problem[problem.size() - 3].c_str(), "%d,%d", &i, &j);
    this->startPoint = &matrix[i][j];
    // Initializes the goal point
    sscanf(problem[problem.size() - 2].c_str(), "%d,%d", &i, &j);
    this->goalPoint = &matrix[i][j];
}

State<Point>* Matrix::getInitialState() {
    return this->startPoint;
}

State<Point>* Matrix::getGoalState() {
    return this->goalPoint;
}

// Returns the all neighbors of given state
vector<State<Point>*> Matrix::getAllPossibleStates(State<Point> *s) {
    vector<State<Point>*> adj_vec;
    int x = s->getState()->getX();
    int y = s->getState()->getY();

    // Check state up limit
    if (y != 0 && (this->matrix[x][y - 1].getCost() != -1)) {
        adj_vec.push_back(&this->matrix[x][y - 1]);
    }
    // Check state left limit
    if (x != 0 && (this->matrix[x - 1][y].getCost() != -1)) {
        adj_vec.push_back(&this->matrix[x - 1][y]);
    }
    // Check state down limit
    if (y != col - 1 && (this->matrix[x][y + 1].getCost() != -1)) {
        adj_vec.push_back(&this->matrix[x][y + 1]);
    }
    // Check state right limit
    if (x != row - 1 && (this->matrix[x + 1][y].getCost() != -1)) {
        adj_vec.push_back(&this->matrix[x + 1][y]);
    }

    return adj_vec;
}

bool Matrix::isGoalState(State<Point> *state) {
    return this->goalPoint->getState() == state->getState();
}

vector<string> Matrix::deleteSpaces(vector<string> vec) {
    vector<string> new_vec;
    for (int k = 0; k < vec.size(); ++k) {
        int l = 0;
        string temp = vec[k];
        string new_str = "";
        while (l < temp.size()) {
            if (temp[l] != ' ') {
                new_str += temp[l];
            }
            l++;
        }
        new_vec.push_back(new_str);
    }
    return new_vec;
}

double Matrix::calculateHeuristic(State<Point> *current, State<Point> *goal) {
    double x = abs(current->getState()->getX() - goal->getState()->getX());
    double y = abs(current->getState()->getY() - goal->getState()->getY());
    return sqrtf(pow(x, 2) + pow(y, 2));
}

