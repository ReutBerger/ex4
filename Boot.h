//
// Created by reut on 1/26/20.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H

#include "MySerialServer.h"
#include "StringReverse.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "MyParallelServer.h"
#include "AStar.h"
#include "MyClientHandler.h"
#include "SearchSolver.h"

namespace boot {
    class Main {
    public:
        int main(int port) {
            try {
                // Part 3 of this project - trying parallelServer on 'searchSolver' problem of Matrix
                int capacity = 5;
                MyParallelServer *mps = new MyParallelServer();
                CacheManager<string> *cm = new FileCacheManager(capacity);
                // Run the project whit a star algorithm, cause according to the trail is the best searcher
                Searcher<Point> *aStar = new AStar<Point>();
                Solver<vector<string>, string> *solver = new SearchSolver(aStar);
                ClientHandler *c = new MyClientHandler(solver, cm);
                mps->open(port, c);
                mps->stop();

                // Part 2 of this project - trying serialServer on 'string reverse' problem
                //MySerialServer *mss = new MySerialServer();
                //Solver<string ,string> *sr = new StringReverse();
                //CacheManager<string> *cm2 = new FileCacheManager(capacity);
                //ClientHandler *ch = new MyTestClientHandler(sr, cm2);
                //mss->open(port, ch);
                //mss->stop();
            } catch (const char *e) {
                cout << e << endl;
            }
            // TODO: delete all new members
            return 0;
        }
    };
}
#endif //EX4_BOOT_H




