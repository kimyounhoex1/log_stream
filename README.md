# log_stream

### 사용법

1. 클론
`````
git clone https://github.com/kimyounhoex1/log_stream.git
cd log_collector
`````
2. 빌드 디렉토리 생성
`````
mkdir build
`````

3. 빌드 (컴파일)
`````
cmake --build build
`````

4. 테스트
````
cd build
ctest 
````

 4.1. 재 태스트
 `````
 rm -rf build
 mkdir build
 cmake -S . -B build
 cmake --build build
 `````




### 최종 디렉토리 구조

`````
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
`````