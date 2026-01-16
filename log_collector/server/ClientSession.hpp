#pragma once
#include "EpollLoop.hpp"
#include <string>
#include <vector>

class ClientSession {
public:
    ClientSession(int fd, EpollLoop& loop);
    void start();

private:
    int fd;
    EpollLoop& loop;
    std::string buffer;
    void onData();
};