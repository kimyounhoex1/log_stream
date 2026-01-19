# log_stream

### 최종 디렉토리 구조

````
log_collector/
├── src/
│   ├── main.cpp
│   ├── server/
│   │   ├── TcpServer.hpp
│   │   ├── TcpServer.cpp
│   │   ├── ClientSession.hpp
│   │   ├── ClientSession.cpp
│   │   ├── EpollLoop.hpp
│   │   ├── EpollLoop.cpp
│   │   ├── MessageQueue.hpp
│   │   └── MessageQueue.cpp
│   ├── utils/
│   │   ├── Logger.hpp
│   │   └── Logger.cpp
│   └── core/
│       ├── LogEntry.hpp
│       ├── LogParser.hpp
│       ├── LogParser.cpp
│       ├── DBWriter.hpp
│       ├── DBWriter.cpp
│       └── Pipeline.hpp
├── CMakeLists.txt
└── README.md
````