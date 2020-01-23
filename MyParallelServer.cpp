//
// Created by reut on 1/22/20.
//

#include "MyParallelServer.h"
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

static int openServer(MyParallelServer* obj) {
    return obj->openServerFunc();
}

void MyParallelServer::open(int port, ClientHandler *c) {
    this->socketfd = -1;
    this->m_port = port;
    this->m_ch = c;

    // Launch the server thread
    thread thread_obj(openServer, this);
    thread_obj.join();
}

int MyParallelServer::openServerFunc() {
    int rc;
    fd_set rfds;
    struct sockaddr_in clientname;

    //create socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(this->m_port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Could not bind the socket to an IP" << endl;
        close(socketfd);
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 12) == -1) { //can also set to SOMAXCON (max connections)
        cerr << "Error during listening command" << endl;
        close(socketfd);
        return -3;
    }
    cout << "Server is now listening ..." << endl;

    // Time-out is set for 2 minutes
    struct timeval tv = {0};
    tv.tv_sec = 120;

    /* Initialize the set of active sockets. */
    FD_ZERO (&rfds);
    FD_SET (socketfd, &rfds);

    while (1)
    {
        /* Block until input arrives on one or more active sockets. */
        rc = select (FD_SETSIZE, &rfds, NULL, NULL, &tv);
        if (rc < 0) {
            perror ("select");
            return -4;
        }
        else if (rc == 0) {
            cout << "timeout" << endl;
            break;
        }
        else {
            /* Service all the sockets with input pending. */
            for (int i = 0; i < FD_SETSIZE; ++i) {
                if (FD_ISSET (i, &rfds)) {
                    if (i == socketfd) {
                        /* Connection request on original socket. */
                        int size = sizeof(clientname);
                        int newsock = accept(socketfd, (struct sockaddr *) &clientname, (socklen_t *) &size);
                        if (newsock < 0) {
                            cerr << "accept() failure" << endl;
                            continue;
                        }

                        cout << "Parallel Server: connect from host " << inet_ntoa(clientname.sin_addr)
                             << "port " << ntohs(clientname.sin_port) << "." << endl;

                        FD_SET (newsock, &rfds);
                    } else {
                        /* Data arriving on an already-connected socket. */
                        if (m_ch->handleClient(i) < 0) {
                            close(i);
                            FD_CLR (i, &rfds);
                        }
                    }
                }
            }
        }
    }

    // Close all client sockets (list / vector)
    // TODO:

    return 0;
}

void MyParallelServer::stop() {
    //closing the listening socket
    if (socketfd != -1) {
        close(socketfd);
        socketfd = -1;
    }
}
