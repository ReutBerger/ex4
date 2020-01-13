//
// Created by reut on 1/12/20.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"

class MyTestClientHandler : public ClientHandler {
private:
   // Solver solver;
   // CacheManger am;
public:
    void handleClient(int socket_client) override ;
};


#endif //EX4_MYTESTCLIENTHANDLER_H
