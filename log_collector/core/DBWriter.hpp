#pragma once
#include "LogEntry.hpp"
#include "MessageQueue.hpp"
#include <thread>
#include <atomic>

class DBWriter {
public:
    DBWriter(MessageQueue<LogEntry>& queue);
    ~DBWriter();
    void start();
    void stop();

private:
    void run();
    MessageQueue<LogEntry> &queue;
    std::thread worker;
    std::atomic<bool> running;
};