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
        server.run();
    }
    catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}