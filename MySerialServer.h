//
// Created by reut on 1/12/20.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include <semaphore.h>
#include "server_side.h"
using namespace server_side;

class MySerialServer : public Server {
private:
    int m_port;
    ClientHandler *m_ch;
    sem_t m_sync;

public:
    void open(int port, ClientHandler* c);
    void stop();
    int openServerFunc();
};


#endif //EX4_MYSERIALSERVER_H
