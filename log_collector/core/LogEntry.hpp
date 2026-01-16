#pragma once
#include <string>

// 로그 구조체
/*
    
*/
struct LogEntry {
    std::string timestamp;
    std::string level;
    std::string host;
    int pid;
    std::string message;
};