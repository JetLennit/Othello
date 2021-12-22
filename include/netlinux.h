#ifndef NET_H
#define NET_H

#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <vector>
#include <iostream>

class Client {

};

class Server {
    public:
        Server();
        void closeServer();
        char getMessage();
        void sendMessage(char message);
    private:
        int sockfd, newsockfd;
        unsigned int clilen;
        int portno = 25564;
        char buffer[255];
        struct sockaddr_in serv_addr, cli_addr;
};

#endif
