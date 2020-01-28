//
// Created by reut on 1/12/20.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

//using namespace std;

class ClientHandler {
public:
    virtual int handleClient(int socket_client) = 0;
    virtual void setupClient(int socket_client) {}
};

#endif //EX4_CLIENTHANDLER_H
