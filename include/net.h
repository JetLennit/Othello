#ifndef NET_H
#define NET_H

#include <iostream>

class Client {

};

class Server {
    public:
        Server();
    private:
        int sockfd, newsockfd;
        unsigned int clilen;
        int portno = 25564;
        char buffer[16];
        struct sockaddr_in serv_addr, cli_addr;
};

#endif
