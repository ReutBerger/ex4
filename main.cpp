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
   State<Point> *s = new State<Point>(new Point(0,0),4);
   State<Point> *v = new State<Point>(new Point(0,0),4);
   cout << s->getCost();
}
#endif //EX4_BOOT_H
