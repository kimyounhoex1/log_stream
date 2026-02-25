#pragma once
#include <iostream>
#include <vector>

struct CollectorConfig {
    std::string host;
    int port;
};

/*
 * client id 
 * 수집할 로그파일의 경로
 * 수집할 포트번호 (소켓 수립)
*/
struct AgentConfig {
    std::string id;
    std::vector<std::string> paths;
    CollectorConfig collector;
};

class Config {
public:
    //json 형태로 설정
    void loadFromFile(const std::string& path);
    const AgentConfig& agent() const;

    std::string readFileContents(const std::string &path);
    
private:
    AgentConfig agent_config;
};