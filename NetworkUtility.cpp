//
// Created by excel on 6/29/2025.
//
#pragma once

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>




void PrintIpAddresses(std::string WebAddress="www.example.com", std::string PortNumber="80" ) {
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo, *currentAddress;
    char ipstr[INET6_ADDRSTRLEN];


    memset(&hints, 0, sizeof(hints)); //sets the info in hint to zeros basically empties it
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(WebAddress.c_str(), PortNumber.c_str(), &hints, &servinfo)) != 0) { // check if this is a valid address
        std::cerr << "Error Getting Address\n";
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        exit(1);
    }

    for (currentAddress= servinfo; currentAddress!= nullptr; currentAddress= currentAddress->ai_next) { // for each value in the result we print the ip adress and type
        std::string Ipver;
        void *addr;
        struct sockaddr_in *ip4;
        struct sockaddr_in6 *ip6;

        if (currentAddress->ai_family == AF_INET) {
            ip4 = reinterpret_cast<struct sockaddr_in *>(currentAddress->ai_addr);
            addr = &(ip4->sin_addr);
            Ipver = "IPv4";
        } else {
            ip6 = reinterpret_cast<struct sockaddr_in6 *>(currentAddress->ai_addr);
            addr = &(ip6->sin6_addr);
            Ipver = "IPv6";
        }
        inet_ntop(currentAddress->ai_family, addr, ipstr, sizeof ipstr);
        std::cout << Ipver << " " << ipstr << std::endl;
    }
    std::cin.get();
    freeaddrinfo(servinfo);
}

