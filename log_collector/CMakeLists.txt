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
# jsoncpp
# =========================
FetchContent_Declare(
    jsoncpp
    URL https://github.com/open-source-parsers/jsoncpp/archive/refs/tags/1.9.5.zip
)

set(JSONCPP_WITH_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(jsoncpp)

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

target_link_libraries(
    log_collector PRIVATE
    jsoncpp_lib
    pqxx
    pq
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

add_executable(
    config_test
    test/ConfigTest.cpp
    client/Config.cpp
)

target_include_directories(
    log_parser_test PRIVATE
    core
)

target_include_directories(
    config_test PRIVATE
    client
    core
    server
)

 target_compile_definitions(config_test PRIVATE
          CONFIG_JSON_PATH="${CMAKE_CURRENT_SOURCE_DIR}/test/config.json")

target_link_libraries(
    log_parser_test
    GTest::gtest_main
    jsoncpp_lib
    pthread
)

target_link_libraries(
    config_test
    GTest::gtest_main
    jsoncpp_lib
)

include(GoogleTest)
gtest_discover_tests(log_parser_test)
gtest_discover_tests(config_test)

link_directories(/usr/lib/aarch64-linux-gnu)
