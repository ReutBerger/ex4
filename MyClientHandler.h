//
// Created by reut on 1/19/20.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "Matrix.h"

class MyClientHandler : public ClientHandler {
private:
    Solver<Matrix,string> *m_solver;
    CacheManager<string> *m_cache;
public:
    MyClientHandler(Solver<Matrix,string> *solver, CacheManager<string> *cache);
    void handleClient(int socket_client) override;
};



#endif //EX4_MYCLIENTHANDLER_H
