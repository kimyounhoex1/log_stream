#pragma once
#include "EpollLoop.hpp"
#include <unordered_map>
#include <memory>

class TcpServer {
public:
    TcpServer(int port);
    void run();
private:
    int listen_fd;
    EpollLoop loop;
    void acceptConnection();
};