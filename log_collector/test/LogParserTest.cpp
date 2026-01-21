#pragma once
#include <gtest/gtest.h>
#include "../core/LogEntry.hpp"
#include "../core/LogParser.hpp"

/*
struct LogEntry {
    std::string timestamp;
    std::string level;
    std::string host;
    int pid;
    std::string message;
};
*/
TEST(LogParserTest, ParseValidLogLine) {
    LogParser parser;

    std::string line = "[2026-01-18 14:32:00][INFO][host1][1234] it's test line for good parsing";

    auto result = parser.parse(line);

    ASSERT_TRUE(result.has_value());

    const LogEntry& entry = result.value();

    EXPECT_EQ(entry.timestamp, "2026-01-18 14:32:00");
    EXPECT_EQ(entry.level, "INFO");
    EXPECT_EQ(entry.host, "host1");
    EXPECT_EQ(entry.pid, 1234);
    EXPECT_EQ(entry.message, "it's test line for good parsing");
}

TEST(LogParserTest, InvalidFormatThrows) {
    LogParser parser;

    std::string broken_line = "this is not a log, so throw this log.";

    auto broken_entry = parser.parse(broken_line);

    EXPECT_FALSE(broken_entry.has_value());
}

