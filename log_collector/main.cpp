#include "server/TcpServer.hpp"
#include <iostream>
#include "core/Pipeline.hpp"

Pipeline* globalPipeline = nullptr;

int main() {
    static Pipeline pipeline;
    globalPipeline = &pipeline;
    
    std::cout << "log_collector starting...\n";

    TcpServer server(8081);   // 너 코드 생성자에 맞게 수정
    server.run();

    return 0;
}