// tests/FakeWriter.hpp
#pragma once
#include "../core/LogEntry.hpp"
#include <vector>

class FakeWriter {
public:
    void write(const LogEntry& log) {
        written.push_back(log);
    }

    size_t count() const {
        return written.size();
    }

    const LogEntry& last() const {
        return written.back();
    }

private:
    std::vector<LogEntry> written;
};
