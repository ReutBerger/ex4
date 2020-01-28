//
// Created by reut on 1/19/20.
//

#include <cstring>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>
#include <vector>

#include "MyClientHandler.h"


// Constructor
MyClientHandler::MyClientHandler(Solver<vector<string>, string> *solver, CacheManager<string> *cache) {
    this->m_solver = solver;
    this->m_cache = cache;
}

int MyClientHandler::handleClient(int socket_client) {
    // Retrieve the matrix for this client
    if (this->m_data_map.find(socket_client) == this->m_data_map.end()) {
        cerr << "Data container not found for socket " << socket_client << endl;
        return -1;
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

    //cout << "sock: " << socket_client << ", line: " << buffer << endl;

    // Add the new line to the matrix
    vec_problem.push_back((string)buffer);

    // When we get the last line, find a solution and send back to client
    if (!strcmp(buffer, "end") || !strcmp(buffer, "end\n")) {
	thread threadObj(&MyClientHandler::findSolutionAndSend, this, socket_client, vec_problem);
	threadObj.detach();
        return 0;
    }

    return 1;
}

void MyClientHandler::setupClient(int socket_client) {
    vector<string> vec_problem;
    this->m_data_map[socket_client] = vec_problem;
}

void MyClientHandler::findSolutionAndSend(int s, vector<string> vec_problem) {
    // Build the problem string
    string problem = "";
    for (string s : vec_problem)
        problem += s;
    //cout << "problem: " << problem << endl;

    m_mtx.lock();

    // Get some solution
    string solution;
    if (this->m_cache->find(problem)) {
        // If the problem already exists in the directory, return it
        solution = this->m_cache->get(problem);
    } else {
        // Solve the problem and add it to directory
        solution = this->m_solver->solve(vec_problem);
        this->m_cache->insert(problem, solution);
    }
    //cout << "solution: " << solution << endl;

    // Send the solution to the client
    if (send(s, solution.c_str(), solution.length(), 0) < 0)
        cerr << "Could not send message" << endl;
    close(s);

    m_mtx.unlock();
}
