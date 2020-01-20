//
// Created by reut on 1/12/20.
//

#include "MyTestClientHandler.h"
#include <unistd.h>
#include <netinet/in.h>

void MyTestClientHandler::handleClient(int socket_client){
    cout << "in My Test handle client" << endl;

    // Declare a buffer to get the data
    char buffer[1024] = {0};

    while(1) {
        //reading from client
        int valread = read(socket_client, buffer, sizeof(buffer)-1);

        // If there is nothing to read, break
        if (valread < 0) {
            cerr << "read error" << endl;
            break;
        }

        buffer[valread] = 0;
        string problem = string(buffer);
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