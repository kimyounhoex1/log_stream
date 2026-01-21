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

# 리눅스라 사실 필요 없지만 공식 문서 그대로 둠
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# =========================
# Main binary
# =========================
add_executable(log_collector
    main.cpp
    core/LogParser.cpp
    core/DBWriter.cpp
    server/ClientSession.cpp
    server/EpollLoop.cpp
    server/TcpServer.cpp
)

target_include_directories(log_collector PRIVATE
    core
    server
)

# =========================
# Tests
# =========================
enable_testing()

add_executable(pipeline_test
    test/PipelineTest.cpp
    test/FakeWriter.cpp
    core/LogParser.cpp
)

target_include_directories(pipeline_test PRIVATE
    core
)

target_link_libraries(pipeline_test
    GTest::gtest_main
    pthread
)

include(GoogleTest)
gtest_discover_tests(pipeline_test)
