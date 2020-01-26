//
// Created by eden on 12/01/2020.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H

#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "MyParallelServer.h"
#include "MyClientHandler.h"
#include "State.h"
#include "Point.h"
#include "SearchSolver.h"

#include "CacheManager.h"
#include "FileCacheManager.h"
#include "StringReverse.h"
#include "Matrix.h"
#include "SearchSolver.h"
#include "BFS.h"
#include "DFS.h"
#include "BestFS.h"
#include "AStar.h"

//#define SERIAL_TEST

using namespace std;

namespace boot{
    class Main;
}

class boot::Main {
public:
    static int main(int port) {
        try {
////#ifdef SERIAL_TEST
//            MySerialServer *mss = new MySerialServer();
//            Solver<string ,string> *sr = new StringReverse();
//            CacheManager<string> *cm = new FileCacheManager(5);
//            ClientHandler *c = new MyTestClientHandler(sr, cm);
//            mss->open(port, c);
//            mss->stop();
//////#else
//            MyParallelServer *mps = new MyParallelServer();
//            CacheManager<string> *cm = new FileCacheManager(5);
//            // Run the project whit a star algorithm, cause according to the trail is the best searcher
//            Searcher<Point> * aStar = new AStar<Point>();
//            Solver<vector<string>, string> *solver = new SearchSolver(aStar);
//            ClientHandler *c = new MyClientHandler(solver ,cm);
//            mps->open(port, c);
//            mps->stop();
            //vector<string> vec = {"1,2,3","-1,5,6","7,8,9","0,0","2,2","end"};
           // Searchable<Point> *m = new Matrix(vec);
           // Searcher<Point>* searcher = new BFS<Point>();
            //vector<State<Point>*> BFSsearch = searcher->search(m);


//#endif

            return 0;
        } catch (const char * e) {
            cout << e << endl;
        }
        // TODO: delete all new members
    }
};

int main(int argc, char *argv[]) {
   // boot::Main::main(atoi(argv[1]));
  // State<Point> *s = new State<Point>(new Point(0,0),1);
//   State<Point> *v = s;
//   cout << s->getCost() << endl;
////   if (s->operator==(v))
////       cout << 1;
////   else
////       cout << 0;
   vector<string> vec =
           {
                   "14,10,16,4,17,2,11,15,5,-1",
                   "1,10,6,10,2,7,4,15,1,2",
                   "2,13,3,8,15,20,11,17,12,19",
                   "5,7,14,6,18,13,20,2,8,5",
                   "4,15,-1,20,15,7,11,12,19,2",
                   "4,4,18,14,16,1,-1,1,18,15",
                   "10,5,1,10,17,19,18,0,15,9",
                   "15,10,20,15,0,2,20,3,0,13",
                   "13,2,19,2,-1,8,-1,7,19,15",
                   "-1,12,5,1,5,9,18,11,-1,5",
                   "0,0",
                   "9,9",
                   "end"
           };
//                        {"1,1,3,1,2,3,4,5,4,4,4",
//                         "-1,2,3,1,2,3,4,5,4,4,4",
//                         "1,2,3,1,2,3,4,5,4,4,4",
//                         "1,2,3,1,2,3,4,5,4,4,4",
//                         "1,2,3,1,2,3,4,5,4,4,4",
//                         "1,2,3,1,2,3,4,5,4,4,4",
//                         "1,2,3,1,2,3,4,5,4,4,4",
//                         "1,2,3,1,2,3,4,5,4,4,4",
//                         "1,2,3,1,2,3,4,5,4,4,-1",
//                         "1,2,3,1,2,3,4,5,4,-1,4",
//                         "1,2,3,1,2,3,4,5,4,4,4",
//                         "0,0",
//                         "10,10",
//                         "end"};
//   Searchable<Point> *m = new Matrix(vec);
////   BestFS<Point>* test = new BestFS<Point>();
////   test->search(m);
    Searcher<Point> * bestFS = new BestFS<Point>();
    Searcher<Point> * bFS = new BFS<Point>();
    Searcher<Point> * dFS = new DFS<Point>();
    Searcher<Point> * aStar = new AStar<Point>();
    SearchSolver * solver1 = new SearchSolver(aStar);
    SearchSolver * solver2 = new SearchSolver(bestFS);
    SearchSolver * solver3 = new SearchSolver(bFS);
    SearchSolver * solver4 = new SearchSolver(dFS);
//
   string solu1 = solver1->solve(vec);
    string solu2 = solver2->solve(vec);
    string solu3 = solver3->solve(vec);
    string solu4 = solver4->solve(vec);
  cout << "A Star :" << solu1 << endl;
    cout << "BesFs :" << solu2 << endl;
    cout << "BFS :" << solu3 << endl;
    cout << "DFS :" << solu4 << endl;
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//
//        }
//        cout << endl;
////    }
////    vector<State<Point>> adj_vec = m->getAllPossibleStates(*s);
////    for (auto i :adj_vec)
////        cout << "(" << i.getState()->getX() << ","<< i.getState()->getY() << ")" << endl;
//
//    Searcher<Point>* searcher = new BFS<Point>();
//    vector<State<Point>*> BFSsearch = searcher->search(m);
//    for (auto i :BFSsearch)
//        cout << "BFS: (" << i->getState()->getX() << ","<< i->getState()->getY() << ")" << endl;
//    cout << "number of nodes = " << searcher->getNumberOfNodes() << endl;
}
#endif //EX4_BOOT_H
