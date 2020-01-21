//
// Created by eden on 12/01/2020.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H

#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "State.h"
#include "Point.h"

#include "CacheManager.h"
#include "FileCacheManager.h"
#include "StringReverse.h"
#include "Matrix.h"
#include "BFS.h"

using namespace std;

namespace boot{
    class Main;
}

class boot::Main {
public:
    static int main(int port) {
        try {
            MySerialServer *mss = new MySerialServer();
            Solver<string ,string> *sr = new StringReverse();
            CacheManager<string> *cm = new FileCacheManager(5);
            ClientHandler *c = new MyTestClientHandler(sr, cm);
            mss->open(port, c);
            mss->stop();
            return 0;
        } catch (const char * e) {
            cout << e << endl;
        }
        // TODO: delete all new members
    }
};

int main(int argc, char *argv[]) {
   // boot::Main::main(atoi(argv[1]));
   State<Point> *s = new State<Point>(new Point(0,0),1);
   State<Point> *v = s;
   cout << s->getCost() << endl;
//   if (s->operator==(v))
//       cout << 1;
//   else
//       cout << 0;
   vector<string> vec = {"1,2,3","-1,5,6","7,8,9","0,0","2,2","end"};
   Matrix* m = new Matrix(vec);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "(" << m->matrix[i][j].getState()->getX() << "," << m->matrix[i][j].getState()->getY() <<"," << m->matrix[i][j].getCost() << ")";
        }
        cout << endl;
    }
    vector<State<Point>*> adj_vec = m->getAllPossibleStates(s);
    for (auto i : adj_vec)
        cout << "(" << i->getState()->getX() << ","<< i->getState()->getY() << ")" << endl;

    Searcher<Point>* searcher = new BFS<Point>();
    vector<State<Point>*> BFSsearch = searcher->search(m);
    for (auto i :BFSsearch)
        cout << "BFS: (" << i->getState()->getX() << ","<< i->getState()->getY() << ")" << endl;
}
#endif //EX4_BOOT_H
