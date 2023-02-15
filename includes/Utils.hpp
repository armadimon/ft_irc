#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <map>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>

std::vector<std::string> string_split(std::string str, const char* delimiter);

#endif