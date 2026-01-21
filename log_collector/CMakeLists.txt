cmake_minimum_required(VERSION 3.14)
project(log_collector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================
# GoogleTest (FetchContent)
# =========================
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# =========================
# 파일 대상 목록
# =========================
add_executable(
    log_collector
    main.cpp
    core/LogParser.cpp
    core/DBWriter.cpp
    server/ClientSession.cpp
    server/EpollLoop.cpp
    server/TcpServer.cpp
)
# =========================
# 파일 대상 디렉토리
# =========================
target_include_directories(
    log_collector PRIVATE
    core
    server
)

# =========================
# Tests
# =========================
enable_testing()

add_executable(
    log_parser_test
    test/LogParserTest.cpp
    core/LogParser.cpp
    core/LogEntry.hpp
)

target_include_directories(
    log_parser_test PRIVATE
    core
)

target_link_libraries(
    log_parser_test
    GTest::gtest_main
    pthread
)

include(GoogleTest)
gtest_discover_tests(log_parser_test)
