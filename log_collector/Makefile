# 타겟: 의존성

# CXX: g++ -> CXX 파일을 만들려면 g++ 필요
CXX := g++
#  컴파일 옵션, c++17, 기본 경고 추가 경고 및 최적화 정도, 디버깅 심볼, 스레드 지원
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -g -pthread

# 결과물 실행 파일 명
TARGET := log_collector

# 소스파일 목록
SRC := \
    main.cpp \
    core/LogParser.cpp \
    server/ClientSession.cpp \
    server/EpollLoop.cpp \
    server/TcpServer.cpp

# .cpp -> .o 파일로 변경
OBJ := $(SRC:.cpp=.o)

# make 입력시, log_collector 만들기
all: $(TARGET)

# 실행파일 만드는 규칙
# main.o, LogParser.o ... 들이 필요하다
# g++ ... -o log_collector main.o core/LogParser.o ...
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 첫번째 의존성 (.cpp) -> 결과 파일(.o) 로 변경
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 클린 시 동작
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
