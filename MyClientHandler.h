//
// Created by reut on 1/19/20.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H

#include <mutex>
#include <unordered_map>

#include "CacheManager.h"
#include "ClientHandler.h"
#include "Matrix.h"
#include "Solver.h"

class MyClientHandler : public ClientHandler {
private:
    unordered_map<int, vector<string>> m_data_map;
    mutex m_mtx;
    Solver<vector<string>,string> *m_solver;
    CacheManager<string> *m_cache;

    void findSolutionAndSend(int s, vector<string> vec_problem);

public:
    MyClientHandler(Solver<vector<string>,string> *solver, CacheManager<string> *cache);
    int handleClient(int socket_client) override;
    void setupClient(int socket_client) override;
};

#endif //EX4_MYCLIENTHANDLER_H
