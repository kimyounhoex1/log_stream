#include "LogEntry.hpp"
#include "MessageQueue.hpp"
#include "DBWriter.hpp"

class Pipeline{
public:
    Pipeline() : writer(queue) {
        writer.start();
    };
    ~Pipeline() {
        writer.stop();
    };

    void pushLog(const LogEntry& log) {
        queue.push(log);
    }
private:
    MessageQueue<LogEntry> queue;
    DBWriter writer;
};