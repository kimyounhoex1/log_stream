#pragma once
#include "EpollLoop.hpp"
#include <ClientSession.hpp>
#include <vector>
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
    std::unordered_map<int, std::shared_ptr<ClientSession>> sessions;
};