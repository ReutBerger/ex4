//
// Created by reut on 1/22/20.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H

#include <semaphore.h>
#include "server_side.h"
using namespace server_side;

class MyParallelServer : public Server {
private:
    int socketfd;
    int m_port;
    ClientHandler *m_ch;

public:
    void open(int port, ClientHandler* c) override ;
    void stop() override ;
    int openServerFunc();
};


#endif //EX4_MYPARALLELSERVER_H
