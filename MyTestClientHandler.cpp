//
// Created by reut on 1/12/20.
//

#include <unistd.h>
#include <netinet/in.h>
#include "MyTestClientHandler.h"

// Constructor
int MyTestClientHandler::handleClient(int socket_client){
    cout << "in My Test handle client" << endl;

    // Declare a buffer to get the data
    char buffer[1024] = {0};

    while(true) {
        //reading from client
        int valread = read(socket_client, buffer, sizeof(buffer)-1);

        // If there is nothing to read, break
        if (valread < 0) {
            cerr << "read error" << endl;
            break;
        }
        buffer[valread] = 0;

        string problem = string(buffer);
        cout << "problem: (" << valread << "), " << problem << endl;
        if (!problem.compare("end")) {
            // We got to the last line of the client problem, so close the client socket
            close(socket_client);
            break;
        }

        // Get some solution
        string solution;
        // If the problem already exists in the directory, return it
        if (this->cm->find(problem)) {
            solution = this->cm->get(problem);
        } else {
            // Solve the problem and add it to directory
            solution = this->solver->solve(problem);
            this->cm->insert(problem, solution);
        }
        cout << "solution = " << solution << endl;

        // Send the solution to the client
        char* s = &solution[0];
        int is_sent = send(socket_client, s, solution.length(), 0);
        if (is_sent == -1) {
            //error
            cerr << "Could not send message"<<std::endl;
        }
    }

    return 0;
}

MyTestClientHandler::MyTestClientHandler(Solver<string, string>* solver, CacheManager<string>* cm) {
    this->solver = solver;
    this->cm = cm;
}