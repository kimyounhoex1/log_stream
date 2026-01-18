#pragma once
#include <string>
#include <ostream>

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

inline std::ostream& operator<<(std::ostream& os, const LogEntry& log) {
    os << log.timestamp
       << ", " << log.level
       << ", " << log.host
       << ", " << log.pid
       << ", " << log.message << "\n";
    return os; 
}