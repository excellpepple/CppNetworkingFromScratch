#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT "8080"
#define QUESIZE 5


int main()
{
    int sockfd, newsockfd;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage client_addr;
    socklen_t client_addr_len;
    int res;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    char HostName[256];

    if ((res = getaddrinfo(nullptr, PORT, &hints, &servinfo)) != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(res) << std::endl;
        exit(EXIT_FAILURE);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "socket error" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (gethostname(HostName, sizeof(HostName))==-1) {
        std::cerr << "gethostname error" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "HostName: " << HostName << std::endl;
    if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        std::cerr << "bind error" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(sockfd, QUESIZE) == -1) {
        std::cerr << "listen error" << std::endl;
        exit(EXIT_FAILURE);
    }

    client_addr_len = sizeof client_addr;
    if ((newsockfd = accept(sockfd, reinterpret_cast<struct sockaddr *> (&client_addr), &client_addr_len)) == -1) {
        std::cerr << "accept error" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string msg = "Hello World!\n";
    int len = msg.size();
    if (send(newsockfd, msg.c_str(), len, 0) == -1) {
        std::cerr << "send error" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cin.get();
    close(newsockfd);
    close(sockfd);
    freeaddrinfo(servinfo);
}