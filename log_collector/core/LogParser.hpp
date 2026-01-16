#pragma once
#include "LogEntry.hpp"
#include <optional>
#include <regex>

class LogParser {
public:
    static std::optional<LogEntry> parse(const std::string& line);
};
