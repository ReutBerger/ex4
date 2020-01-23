//
// Created by reut on 1/19/20.
//

#include "MyClientHandler.h"
#include <unistd.h>
#include <netinet/in.h>

MyClientHandler::MyClientHandler(Solver<Matrix, string> *solver, CacheManager<string> *cache) {
    this->m_solver = solver;
    this->m_cache = cache;
}

//TODO: implement this.
int MyClientHandler::handleClient(int socket_client) {
    cout << "in My client handler, socket = " << socket_client << endl;

    // Declare a buffer to get the data
    char buffer[5000] = {0};

    //reading from client
    int valread = read(socket_client, buffer, sizeof(buffer) - 1);
    if (valread < 0) {
        cerr << "read error" << endl;
        return -1;
    }

    buffer[valread] = 0;
    string problem = string(buffer);
    cout << "problem: " << problem << endl;
    if (!problem.compare("end")) {
        return 0;
    }

    string solution;
//    if (this->m_cache->find(problem)) {
//        solution = this->m_cache->get(problem);
//    } else {
//        solution = this->m_solver->solve(problem);
//        this->m_cache->insert(problem, solution);
//    }

solution = "fake solution until fix of types";
    cout << "solution = " << solution << endl;

    char *s = &solution[0];
    int is_sent = send(socket_client, s, solution.length(), 0);
    if (is_sent == -1) {
        cerr << "Could not send message" << endl;
        return -3;
    }

    return 0;
}