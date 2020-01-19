//
// Created by reut on 1/19/20.
//

#include "MyClientHandler.h"

MyClientHandler::MyClientHandler(Solver<Matrix, string> *solver, CacheManager<string> *cache) {
    this->m_solver = solver;
    this->m_cache = cache;
}

//TODO: implement this.
void MyClientHandler::handleClient(int socket_client) {

}

