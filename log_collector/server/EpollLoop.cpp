#include "EpollLoop.hpp"
#include <sys/epoll.h>
#include <vector>
#include <unistd.h>

EpollLoop::EpollLoop() {
    epoll_fd = epoll_create1(0);
}

void EpollLoop::addFd(int fd, Callback cb) {
    epoll_event ev{};
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
    handlers[fd] = std::move(cb);
}

void EpollLoop::run() {
    std::vector<epoll_event> events(64);
    while(true) {
        int n = epoll_wait(epoll_fd, events.data(), events.size(), -1);
        for(int i = 0; i<n; ++i) {
            int fd = events[i].data.fd;
            if (handlers.count(fd)) handlers[fd](fd);
        }
    }
}