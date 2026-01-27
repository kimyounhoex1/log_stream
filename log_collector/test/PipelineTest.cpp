// #pragma once
// #include <gtest/gtest.h>
// #include "../core/LogEntry.hpp"
// #include "../core/LogParser.hpp"

// class FakeSink : Public StorageSink {
// public:
//     int called = 0;
//     LogEntry last;

//     void write(const LogEntry& log) override {
//         called++;
//         last=log;
//     }
// };

// TEST(PipelineTest, WritesLogToSink) {
//     auto sink = std::make_unique<FakeSink>();
//     FakeSink* raw = sink.get();

//     Pipeline pipeline(std::move(sink));

//     LogEntry log("INFO", "hello");
//     pipeline.consume(log);

//     EXPECT_EQ(raw->called, 1);
//     EXPECT_EQ(raw->last.message, "hello");
// }
