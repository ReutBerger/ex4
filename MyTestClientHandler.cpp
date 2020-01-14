//
// Created by reut on 1/12/20.
//

#include "MyTestClientHandler.h"

void MyTestClientHandler::handleClient(int socket_client){
    cout << "in handle client" << endl;
    //ToDO: open client , give us string, key=problem
    string problem = "abcd";
    string solution;
    if (this->cm->find(problem)) {
        // TODO: return solution to client
         solution = this->cm->get(problem);
    } else {
        solution = this->solver->solve(problem);
        this->cm->insert(problem, solution);
        // TODO: return solution to client
    }
}

MyTestClientHandler::MyTestClientHandler(Solver<string, string>* solver, CacheManager<string>* cm) {
    this->solver = solver;
    this->cm = cm;
}