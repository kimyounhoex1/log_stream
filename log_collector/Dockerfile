FROM ubuntu:22.04

# 빌드 도구 + 의존성 설치
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libpq-dev \
    libpqxx-dev \
    iproute2 \
    net-tools \
    && rm -rf /var/lib/apt/lists/* 

WORKDIR /app

# 소스 복사
COPY . .

# 빌드
RUN mkdir -p build && cd build && \
    cmake .. && \
    make -j$(nproc)

# 실행
CMD ["./build/bin/log_collector"]