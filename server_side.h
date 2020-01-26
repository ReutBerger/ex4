//
// Created by reut on 1/12/20.
//

#ifndef EX4_SERVER_SIDE_H
#define EX4_SERVER_SIDE_H

#include "ClientHandler.h"

namespace server_side{
    class Server;
}

class server_side:: Server {
public:
     virtual void open(int port, ClientHandler* c) = 0;
     virtual void stop() = 0;
     virtual int openServerFunc() = 0;
};

#endif //EX4_SERVER_SIDE_H
