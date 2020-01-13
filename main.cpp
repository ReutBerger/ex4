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

#include "StringReverse.h"
class boot::Main {
public:
    static int main(int port) {
        MySerialServer* mss = new MySerialServer();
        ClientHandler *c  = new MyTestClientHandler();
        mss->open(port, c);

        StringReverse *sr = new StringReverse();
        cout << sr->Solve("abcd") << endl;
        return 0;
    }
};

int main(int argc, char *argv[]) {
//    boot::Main::main(atoi(argv[1]));
    boot::Main::main(atoi("5400"));
}
#endif //EX4_BOOT_H
