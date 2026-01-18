#pragma once
#include "EpollLoop.hpp"
#include <memory>
#include <string>
#include <vector>

class ClientSession : public std::enable_shared_from_this<ClientSession> {
public:
    ClientSession(int fd, EpollLoop& loop);
    void start();

private:
    int fd;
    EpollLoop& loop;
    std::string buffer;
    void onData();
};
