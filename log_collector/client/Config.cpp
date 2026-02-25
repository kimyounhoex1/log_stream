#include "Config.hpp"
#include <fstream>
#include <iostream>
#include <json/json.h>

std::string Config::readFileContents(const std::string &path) {
    std::ifstream file(path);
    std::string s;
    if(!file.is_open()) {
        std::cerr << "파일 열 수 없음" << std::endl;
        return "";
    }

    file.seekg(0, std::ios::end);
    int size = file.tellg();
    s.resize(size);
    file.seekg(0, std::ios::beg);
    file.read(&s[0], size);
    std::cout << s << std::endl;

    file.close();
    return s;
}

void Config::loadFromFile(const std::string &path)
{
    // 1. 파일 열기
    readFileContents(path);
    // 2. Json 파싱
    // 3. agent_config 채우기

    // 4. validation
    
}

const AgentConfig &Config::agent() const
{
    return agent_config;
}
