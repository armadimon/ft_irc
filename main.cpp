#include <iostream>
#include "includes/Server.hpp"

int main(int argc, char** argv) {

    if (argc != 3) {
        std::cout << "Usage : ./ircserv <port> <password> " << std::endl;
        exit(1);
    }
    
    Server server;
    server.setPort(argv[1]);
    server.setPass(argv[2]);
    try {
    }
    catch (std::exception &e) {
        e.what();
    }

    return 0;
}