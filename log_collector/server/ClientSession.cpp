#include "ClientSession.hpp"
#include "../core/Pipeline.hpp"
#include "../core/LogParser.hpp"
#include <unistd.h>
#include <iostream>

extern Pipeline* globalPipeline;

ClientSession::ClientSession(int fd, EpollLoop& loop, std::function<void(int)> onClose)
    : fd(fd), loop(loop), onClose(std::move(onClose)) {}

void ClientSession::start() {
    auto self = shared_from_this();
    loop.addFd(fd, [self](int fd) {
         self->onData(); 
    });
}

void ClientSession::onData() {
    char buf[1024];
    ssize_t n = read(fd, buf, sizeof(buf));
    if(n <= 0) {
        loop.removeFd(fd);
        close(fd);
        if (onClose)
            onClose(fd);
        return;
    }

    buffer.append(buf, n);

    size_t pos;
    while((pos = buffer.find('\n')) != std::string::npos) {
        std::string line = buffer.substr(0, pos);
        buffer.erase(0, pos+1);
        
        auto parsed = LogParser::parse(line);
        if (parsed) {
            globalPipeline->pushLog(*parsed);
        }
        std::cout << "[LOG] " << line << std::endl;
    }
}