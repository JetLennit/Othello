#include "netlinux.h"

Server::Server(){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        std::cerr << "ERROR opening socket" << std::endl;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
        sizeof(serv_addr)) < 0)
        std::cerr << "ERROR on binding" << std::endl;
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
         std::cerr << "ERROR on accept" << std::endl;
    bzero(buffer,256);
}

void Server::closeServer() {
    close(newsockfd);
}

char Server::getMessage() {
    int n;
    n = read(newsockfd,buffer,255);
    if (n < 0) 
        std::cout << "ERROR reading from socket" << std::endl;
    return buffer[0];
}

void Server::sendMessage(char message) {
    int n;
    n = write(newsockfd,&message,1);
    if (n < 0) std::cerr << "ERROR writing to socket" << std::endl;
}
