#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>

/* message queue 절차

    producer(생성)
        1. 잠구기
        2. 큐에 데이터 넣기
        3. 대기중인 소비자 깨우기
    Consumer(소비)
        1. 락 풀었다가 다시 잡기 (그래서 lock_guard -> unique_lock으로)
        2. 조건 만족할때까지 대기
        3. 데이터 꺼내기
*/

/*
    1. 로그 네트워크를 통한 전송 -> producer
    2. 로그 파싱 처리 이전에 큐 저장(로그 수집이 훨씬 빠르기 때문에, 파싱 처리 db 저장 중에 네트워크 손실 발생)
    3. 하나씩 꺼내서 파싱 및 db 처리 -> consumer
*/
template<typename T>
class MessageQueue {
private:
    std::queue<T> que;
    std::mutex mtx;
    std::condition_variable cv;
public:
    void push(const T& msg) {
        // lock 걸기
        std::lock_guard<std::mutex> lock(mtx);
        // queue 안에 넣기
        std::cout << "[Queue] push \n";
        que.push(msg);
        // consumer에게 알림
        cv.notify_one();
    }

    T pop() {
        // 꺼내는 작업시에, cpu 잠금
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "[Queue] pop \n";
        // 락으로, 큐 작업 잠금 (큐가 공유자원)
        cv.wait(lock, [this] {
            return !que.empty();
        });
        // 큐에서 값을 꺼내고, 값 가져옴
        T val = que.front();
        que.pop();
        std::cout << "[Queue] pop data = " << val << "\n";
        return val;
    }
};