//
// Created by reut on 1/19/20.
//

#include "MyClientHandler.h"
#include <unistd.h>
#include <netinet/in.h>

MyClientHandler::MyClientHandler(Solver<vector<string>, string> *solver, CacheManager<string> *cache) {
    this->m_solver = solver;
    this->m_cache = cache;
}

//TODO: implement this.
int MyClientHandler::handleClient(int socket_client) {
    cout << "in My client handler, socket = " << socket_client << endl;

    // Declare a buffer to get the data
    char buffer[5000] = {0};
    vector<string> vec_problem;
    string string_problem = "";
    //reading from client
    while (true) {
        int valread = read(socket_client, buffer, sizeof(buffer) - 1);
        if (valread < 0) {
            cerr << "read error" << endl;
            return -1;
        }

        buffer[valread] = 0;
        string problem = string(buffer);
        cout << "problem: " << problem << endl;
        vec_problem.push_back(problem);
        string_problem += problem;
        if (!problem.compare("end")) {
            break;
        }
    }


    string solution;
    if (this->m_cache->find(string_problem)) {
        solution = this->m_cache->get(string_problem);
    } else {
        solution = this->m_solver->solve(vec_problem);
        this->m_cache->insert(string_problem, solution);
    }

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