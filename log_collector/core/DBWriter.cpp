#include "DBWriter.hpp"
#include "MessageQueue.hpp"
#include "LogEntry.hpp"

DBWriter::DBWriter(MessageQueue<LogEntry>& queue) :
queue(queue), running(false) {}

DBWriter::~DBWriter() {
    stop();
}

void DBWriter::start() {
    running = true;
    worker = std::thread(&DBWriter::run, this);
}

void DBWriter::stop() {
    bool wasRunning = running.exchange(false);
    if (wasRunning) {
        queue.push(LogEntry{}); // wake the worker so it can exit
        if(worker.joinable()) 
            worker.join();
    }
}

void DBWriter::run() {
    while(true) {
        auto log = queue.pop();
        if(!running && log.timestamp.empty() && log.level.empty() &&
            log.host.empty() && log.pid == 0 && log.message.empty()) {
            break;
        }
        std::cout << "[DB-INSERT]"
            << log.timestamp << " | "
            << log.level << " | "
            << log.host << " | "
            << log.pid << " | "
            << log.message << std::endl;
    }
}
