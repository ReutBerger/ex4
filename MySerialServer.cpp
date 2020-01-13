//
// Created by reut on 1/12/20.
//
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "MySerialServer.h"

using namespace std;

// C function, start point of the thread
static int openServer(MySerialServer* obj) {
    return obj->openServerFunc();
}

void MySerialServer::open(int port, ClientHandler* c) {
    this->m_port = port;
    this->m_ch = c;

    // Launch the server thread
    thread thread_obj(openServer, this);

    // wait until the simulator is connected
    sem_init(&this->m_sync, 0, 0);
    sem_wait(&this->m_sync);

    // Return to the main thread
    thread_obj.detach();
    sem_destroy(&this->m_sync);
}

void MySerialServer::stop(){

}

int MySerialServer::openServerFunc(){

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //todo: throw exp??
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
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        cerr << "Error during listening command" << endl;
        return -3;
    } else{
        cout << "Server is now listening ..." << endl;
    }

    // accepting the clients in serial
int i = 0;
    while (i < 10) {
        // accepting a client
        int client_socket = accept(socketfd, (struct sockaddr *)&address,
                                   (socklen_t*)&address);

        if (client_socket == -1) {
            cerr << "Error accepting client" << endl;
            return -4;
        }
        this->m_ch->handleClient(client_socket);

        i++;
    }


    close(socketfd); //closing the listening socket

    //reading from client

}