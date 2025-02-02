//
// Created by reut on 1/22/20.
//

#include <iostream>
#include <list>
#include <thread>
#include <unistd.h>
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "MyParallelServer.h"

using namespace std;

void MyParallelServer::open(int port, ClientHandler *c) {
    this->socketfd = -1;
    this->m_port = port;
    this->m_ch = c;

    // Launch the server thread
    thread thread_obj(&MyParallelServer::openServerFunc, this);
    thread_obj.join();
}

int MyParallelServer::openServerFunc() {
    list<int> sockestsList;
    vector<int> sockestsVec;
    int retVal = 0;
    int rc;
    fd_set rfds, active_rfds;
    struct sockaddr_in clientname;


    //create socket
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketfd == -1) {
        //error
        cerr << "Could not create a socket"<<endl;
        return -1;
    }

    int enable = 1;
    setsockopt(this->socketfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    setsockopt(this->socketfd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(enable));

    //bind socket to IP address
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->m_port);

    //the actual bind command
    if (bind(this->socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Could not bind the socket to an IP" << endl;
        close(this->socketfd);
        return -2;
    }

    //making socket listen to the port
    if (listen(this->socketfd, 12) == -1) { //can also set to SOMAXCON (max connections)
        cerr << "Error during listening command" << endl;
        close(this->socketfd);
        return -3;
    }
    cout << "Server is now listening ..." << endl;

    /* Initialize the set of active sockets. */
    FD_ZERO (&active_rfds);
    FD_SET (this->socketfd, &active_rfds);

    while (true)
    {
        // Time-out is set for 2 minutes
        struct timeval tv = {120, 0};

        // Block until input arrives on one or more active sockets
        rfds = active_rfds;
        rc = select (FD_SETSIZE, &rfds, NULL, NULL, &tv);
        if (rc < 0) {
            perror ("select");
            retVal = -4;
            break;
        }
        else if (rc == 0) {
            cout << "timeout" << endl;
            retVal = -5;
            break;
        }
        else {
            // Service all the sockets with input pending
            for (int i = 0; i < FD_SETSIZE; ++i) {
                if (FD_ISSET (i, &rfds)) {
                    if (i == this->socketfd) {
                        // Connection request on original socket
                        int size = sizeof(clientname);
                        int newsock = accept(this->socketfd, (struct sockaddr *) &clientname, (socklen_t *) &size);
                        if (newsock < 0) {
                            cerr << "accept() failure" << endl;
                            continue;
                        }
                        // Push all new sockets to a vector
                        sockestsVec.push_back(newsock);

                        cout << "Parallel Server: connect from host " << inet_ntoa(clientname.sin_addr)
                             << "port " << ntohs(clientname.sin_port) << "." << endl;

                        this->m_ch->setupClient(newsock);

                        FD_SET (newsock, &active_rfds);
                    } else {
                        // Data arriving on an already-connected socket
			int rc;
                        if ((rc = this->m_ch->handleClient(i)) <= 0) {
                            if (rc < 0) close(i);
                            FD_CLR (i, &active_rfds);
                            }
                        }
                    }
                }
            }
        }

    return retVal;
}

void MyParallelServer::stop() {
    //closing the listening socket
    if (this->socketfd != -1) {
        close(this->socketfd);
        this->socketfd = -1;
    }
}
