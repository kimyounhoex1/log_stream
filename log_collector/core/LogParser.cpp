#include "LogParser.hpp"

static std::optional<LogParser>::LogParser parse(const std::string& line) {
    std::regex re(R"(\[(.*?)\]\[(.*?)\]\[(.*?)\]\[(\d+)\]\s*(.*))");
    std::smatch match;

    if(std::regex_match(line, match, re)) {
        LogEntry entry{
            match[1], match[2], match[3], std::stoi(match[4]), match[5]
        };
        return entry;
    }

    return std::nullptr
}