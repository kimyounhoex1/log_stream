#include "LogEntry.hpp"

// 지금은 postgreesql만 이지만, 이제 확장 해나갈 거임.
class LogSink {
public:
    virtual ~LogSink() = default;
    virtual void write(const LogEntry& log) = 0;
};