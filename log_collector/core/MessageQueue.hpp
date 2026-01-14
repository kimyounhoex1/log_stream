#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class MessageQueue {
public:
    void push(const T& msg) {
        std::lock_guard<std::mutex> lock(mtx);
        q.push(msg);
        cv.notify_one();
    }

    T pop() {
        std::unqiue_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] {
            return !q.empty();
        });
        T val = q.front();
        q.pop();
        return val;
    }

private:
    std::queue<T> q;
    std::mutex mtx;
    std::condition_variable cv;
};