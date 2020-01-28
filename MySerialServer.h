//
// Created by reut on 1/12/20.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include "server_side.h"

using namespace server_side;

class MySerialServer : public Server {
private:
    int socketfd;
    int m_port;
    ClientHandler *m_ch;

    int openServerFunc();

public:
    void open(int port, ClientHandler* c) override;
    void stop() override;
};

#endif //EX4_MYSERIALSERVER_H
