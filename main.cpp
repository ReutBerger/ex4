//
// Created by eden on 12/01/2020.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H

#include <iostream>

using namespace std;

namespace boot{
    class Main;
}

#include "StringReverse.h"
class boot::Main {
public:
    static int main(int port) {
        StringReverse *s = new StringReverse();
        cout << s->Solve("abcd") << endl;
        return 0;
    }
};

int main(int argc, char *argv[]) {
//    boot::Main::main(atoi(argv[1]));
    boot::Main::main(atoi("1234"));
}
#endif //EX4_BOOT_H
