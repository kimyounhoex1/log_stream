#pragma once
#include <functional>
#include <unordered_map>

class EpollLoop {
public: 
    using Callback = std::function<void(int)>;

    EpollLoop();
    void addFd(int fd, Callback cb);
    void run();

private:
    int epoll_fd;
    std::unordered_map<int, Callback> handlers;
};