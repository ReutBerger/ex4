//
// Created by reut on 1/12/20.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

#include <iostream>
using namespace std;

class ClientHandler {
public:
    virtual int handleClient(int socket_client) = 0;
};


#endif //EX4_CLIENTHANDLER_H
