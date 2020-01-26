//
// Created by reut on 1/19/20.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H

#include <unordered_map>

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "Matrix.h"

class MyClientHandler : public ClientHandler {
private:
    unordered_map<int, vector<string>> m_data_map;
    Solver<vector<string>,string> *m_solver;
    CacheManager<string> *m_cache;
public:
    MyClientHandler(Solver<vector<string>,string> *solver, CacheManager<string> *cache);
    int handleClient(int socket_client) override;
    void setupClient(int socket_client) override;
};

#endif //EX4_MYCLIENTHANDLER_H
