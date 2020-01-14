//
// Created by reut on 1/12/20.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

class MyTestClientHandler : public ClientHandler {
private:
    Solver<string, string>* solver;
    CacheManager<string>* cm;
public:
    MyTestClientHandler(Solver<string, string>* solver, CacheManager<string>* cm);
    void handleClient(int socket_client) override;
};


#endif //EX4_MYTESTCLIENTHANDLER_H
