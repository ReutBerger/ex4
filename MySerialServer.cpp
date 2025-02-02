//
// Created by reut on 1/12/20.
//

#include <iostream>
#include <thread>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "MySerialServer.h"

using namespace std;

void MySerialServer::open(int port, ClientHandler* c) {
    this->socketfd = -1;
    this->m_port = port;
    this->m_ch = c;

    // Launch the server thread
    thread thread_obj(&MySerialServer::openServerFunc, this);
    thread_obj.join();
}

void MySerialServer::stop(){
    //closing the listening socket
    close(this->socketfd);
}

int MySerialServer::openServerFunc(){

    //create socket
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketfd == -1) {
        //error
        cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    // Time-out is set for 2 minutes
    struct timeval tv = {120, 0};
    setsockopt(this->socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(this->m_port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(this->socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Could not bind the socket to an IP" << endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(this->socketfd, 1) == -1) { //can also set to SOMAXCON (max connections)
        cerr << "Error during listening command" << endl;
        return -3;
    }
    cout << "Server is now listening ..." << endl;

    // accepting the clients in serial
    while (true) {
        // accepting a client
        int addresslen = sizeof (address);
        int client_socket = accept(this->socketfd, (struct sockaddr *)&address, (socklen_t *)&addresslen);
        if (client_socket == -1) {
            cerr << "Error accepting client" << endl;
            return -4;
        }

        // Handle client problems
        this->m_ch->handleClient(client_socket);
    }
}
