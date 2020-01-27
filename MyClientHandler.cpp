//
// Created by reut on 1/19/20.
//

#include "MyClientHandler.h"
#include <unistd.h>
#include <netinet/in.h>
#include <vector>
#include <cstring>

// Constructor
MyClientHandler::MyClientHandler(Solver<vector<string>, string> *solver, CacheManager<string> *cache) {
    this->m_solver = solver;
    this->m_cache = cache;
}

int MyClientHandler::handleClient(int socket_client) {
    // Retrieve the matrix for this client
    if (this->m_data_map.find(socket_client) == this->m_data_map.end()) {
        cerr << "Data container not found for socket " << socket_client << endl;
        return -4;
    }
    vector<string>& vec_problem = this->m_data_map[socket_client];

    //reading from client
    char buffer[5120];
    int valread = read(socket_client, buffer, sizeof(buffer) - 1);
    if (valread < 0) {
        cerr << "read error" << endl;
        return -1;
    }
    buffer[valread] = 0;

    /*TRY*/cout << "sock:" << socket_client << ", line: " << buffer << endl;

    // Add the new line to the matrix
    vec_problem.push_back((string)buffer);

    // When we get the last line, find a solution and send back to client
    if (!strcmp(buffer, "end")) {
        string string_problem;
        string_problem = "";
        for (string s : vec_problem) {
            string_problem += s;
        }
        /*TRY*/cout << "problem: " << string_problem << endl;

        // Get some solution
        string solution;
        // If the problem already exists in the directory, return it
        if (this->m_cache->find(string_problem)) {
            solution = this->m_cache->get(string_problem);
        } else {
            // Solve the problem and add it to directory
            solution = this->m_solver->solve(vec_problem);
            this->m_cache->insert(string_problem, solution);
        }
        /*TRY*/cout << "solution = " << solution << endl;

        // Send the solution to the client
        int is_sent = send(socket_client, solution.c_str(), solution.length(), 0);
        if (is_sent == -1) {
            cerr << "Could not send message" << endl;
            return -3;
        }

        return 0;
    }

    return 1;
}

void MyClientHandler::setupClient(int socket_client) {
    vector<string> vec_problem;
    this->m_data_map[socket_client] = vec_problem;
}
