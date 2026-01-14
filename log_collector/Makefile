CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -g -pthread

TARGET := log_collector

SRC := \
    main.cpp \
    core/LogParser.cpp \
    server/ClientSession.cpp \
    server/EpollLoop.cpp \
    server/TcpServer.cpp

OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
