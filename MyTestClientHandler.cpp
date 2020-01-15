//
// Created by reut on 1/12/20.
//

#include "MyTestClientHandler.h"
#include <unistd.h>
#include <netinet/in.h>

void MyTestClientHandler::handleClient(int socket_client){
    cout << "in handle client" << endl;

    // Declare a buffer to get the data
    char buffer[1024] = {0};

    while(1) {
        //reading from client
        int valread = read(socket_client, buffer, 1024);

        // If there is nothing to read, break
        if (valread == 0) {
            break;
        }
        string problem = string(buffer);
        problem = problem.substr(0, valread);
        cout << "problem: " << problem << endl;
        if (!problem.compare("end")) {
            close(socket_client);
            break;
        }
        string solution;
        if (this->cm->find(problem)) {
            solution = this->cm->get(problem);
        } else {
            solution = this->solver->solve(problem);
            this->cm->insert(problem, solution);
        }
        cout << "solution = " << solution << endl;

        char* s = &solution[0];
        int is_sent = send(socket_client, s, solution.length(), 0);
        if (is_sent == -1) {
            //error
            cerr << "Could not send message"<<std::endl;
        }
    }
}

MyTestClientHandler::MyTestClientHandler(Solver<string, string>* solver, CacheManager<string>* cm) {
    this->solver = solver;
    this->cm = cm;
}