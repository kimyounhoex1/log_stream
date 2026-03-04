# log_stream

### 프로젝트 개요

`log_stream 은 **C++ 기반 로그 수집기/분석기**와, 이후 추가될 **Spring 기반 관리/조회 API 서버**를 통해`

`대용량 서비스 로그를 수집하고 분석하는 것을 목표로 하는 프로젝트입니다.`

- **C++ 로그 수집기 (log_collector)**  
  - TCP로 들어오는 로그 스트림을 수신
  - 각 로그를 파싱해서 데이터베이스에 적재
  - 이후 IP 기반 간단 방화벽/차단 기능과 연동될 예정
- **Spring API 서버 (계획)**  
  - DB에 적재된 로그를 조회/필터링/집계하는 REST API를 제공
  - 웹 프론트엔드에서 로그/보안 상태를 확인할 수 있는 페이지를 제공

리눅스 서버 환경, 애플리케이션 로그는 전용 수집기를 통해 직접 처리

---

### 아키텍처 개요

- 애플리케이션(서비스) → C++ 로그 수집기(TCP) → DB(PostgreSQL 등)
- Spring API 서버 → DB에서 로그 조회 → 프론트엔드에 JSON으로 응답
- 필요 시, 로그 파일 백업은 `/var/log/log_stream/`

최종 프로젝트 흐름

```worktree-markdown
> 다이어그램으로 변환 예정
```

```worktree-markdown
flowchart LR
  appClient[App] -->|HTTP 요청 처리| serviceApp[Service]
  serviceApp -->|"로그 전송(JSON/TCP)"| cppCollector[CppLogCollector]
  cppCollector -->|INSERT| logDB[LogDB]
  adminUser[Admin] -->|로그 조회| webUI[WebFrontend]
  webUI --> springApi[SpringAPI]
  springApi --> logDB
```

### 사용법

1. 클론

```
git clone https://github.com/kimyounhoex1/log_stream.git
cd log_collector
```

1. 빌드 디렉토리 생성

```
mkdir build
```

1. 빌드 (컴파일)

```
cmake --build build
```

1. 테스트

```
cd build
ctest
```

4.1. 재 태스트

```
rm -rf build
mkdir build
cmake -S . -B build
cmake --build build
```

### 최종 디렉토리 구조

```
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
```

### DB 테이블 명령어

```worktree-markdown
> 아래 스키마는 초기 버전이며, HTTP 요청/보안 로그에 필요한 필드는 점진적으로 확장 예정
```

```
CREATE TABLE logs (
    id SERIAL PRIMARY KEY,
    timestamp TIMESTAMP,
    level VARCHAR(16),
    host VARCHAR(64),
    pid INT,
    message TEXT
);
```

