//
// Created by eden on 12/01/2020.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H

#include <iostream>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
using namespace std;

namespace boot{
    class Main;
}

#include "CacheManager.h"
#include "FileCacheManager.h"
#include "StringReverse.h"
class boot::Main {
public:
    static int main(int port) {
        MySerialServer* mss = new MySerialServer();
        StringReverse *sr = new StringReverse();
        CacheManager<string>* cm = new FileCacheManager(10);
        ClientHandler *c  = new MyTestClientHandler(sr,cm);
        mss->open(port, c);


        return 0;
    }
};

int main(int argc, char *argv[]) {
    boot::Main::main(atoi(argv[1]));
//    boot::Main::main(atoi("5400"));
}
#endif //EX4_BOOT_H
