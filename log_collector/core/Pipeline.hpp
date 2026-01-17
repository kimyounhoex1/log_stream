#include "LogParser.hpp"
#include "MessageQueue.hpp"

class Pipeline{
public:
    
    ~DataPipeline();

private:
    MessageQueue<LogEntry> queue;
    
};