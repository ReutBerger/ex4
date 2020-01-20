//
// Created by reut on 1/19/20.
//

#include "Matrix.h"
#include <iostream>

// Constructor- build the matrix and update members
Matrix::Matrix(vector<string> problem) {
 //   vector<vector<State<Point>>> matrix;
    int i = 0, j = 0, count = 0;
    string line, temp_num = "";
    while (j < problem.size() - 3) {
        line = problem[j];
        while (line[count] != '\0') {
            temp_num += line[count];
            if (line[count] == ',') {
                temp_num = temp_num.substr(0,count);
                // State<Point>* s = new State<Point>(atoi(temp_num), new Point(i,j))
                /*TRY*/ cout << temp_num <<i << j << endl;
                i++;
                line.erase(0, count + 1);
                temp_num = "";
                count = -1;
            }
            count++;
        }
        if(temp_num != "") {
            // State<Point>* s = new State<Point>(atoi(temp_num), new Point(i,j))
            /*TRY*/ cout << temp_num << i << j << endl;
            temp_num = "";
        }
        count = 0;
        i = 0;
        j++;
    }
}


//TODO - delete - example Matrix
// vector<string> vec = {"1,2,3","4,5,6","7,8,9","0,0","2,2","end"};