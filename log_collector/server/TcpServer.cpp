#include "TcpServer.hpp"
#include "ClientSession.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>


TcpServer::TcpServer(int port) {
    // 서버의 TCP socket 생성 
    // fd generate to TCP
    listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
    // to make non_block tcp, generate flag value
    int flag = fcntl(listen_fd, F_GETFL, 0);
    fcntl(listen_fd, F_SETFL, flag | O_NONBLOCK);

    sockaddr_in addr{};
    addr.sin_family = AF_INET; // ipv4
    addr.sin_port = htons(port); // port
    addr.sin_addr.s_addr = INADDR_ANY; // addr

    bind(listen_fd, (sockaddr*) &addr, sizeof(addr));
    // make server listen status, SOMAXCONN -> kernel max backlog 
    listen(listen_fd, SOMAXCONN);

    loop.addFd(listen_fd, [this](int fd) {
        acceptConnection();
    });
}

void TcpServer::run() {
    std::cout << "[Collector] listening..." << std::endl;
    loop.run();
}

void TcpServer::acceptConnection() {
    sockaddr_in client{};
    socklen_t len = sizeof(client);
    int client_fd = accept4(listen_fd, (sockaddr*)&client, &len, SOCK_NONBLOCK);
    if(client_fd < 0) return;

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client.sin_addr, client_ip, sizeof(client_ip));
    int client_port = ntohs(client.sin_port);

    std::cout << "Client connected: %s:%d (fd=%d)\n" <<
            client_ip << ":" << client_port <<
            "fd=" << client_fd << "\n";
           
    auto session = std::make_shared<ClientSession>(
        client_fd,
        loop,
        [this](int fd) {sessions.erase(fd);}
    );
    sessions[client_fd] = session;
    session->start();
}