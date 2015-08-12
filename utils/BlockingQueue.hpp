#ifndef TOYHTTPD_BLOCKINGQUEUE_HPP
#define TOYHTTPD_BLOCKINGQUEUE_HPP


#include <vector>
#include <queue>
#include <mutex>
#include <cassert>
#include <condition_variable>


template<class T>
class BlockingQueue {
public:
    BlockingQueue() {}
    void push(const T& x) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(x);
        notEmptyCond_.notify_one();
    }

    void pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.size() == 0) {
            notEmptyCond_.wait(lock);
        }
        queue_.pop();
    }

    size_t size() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return queue_.size();
    }

    bool empty() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return queue_.size() == 0;
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable notEmptyCond_;

    BlockingQueue(const BlockingQueue&) = delete;
    const BlockingQueue& operator =(const BlockingQueue&) = delete;
    BlockingQueue(BlockingQueue&&) = delete;
    const BlockingQueue& operator =(BlockingQueue&&) = delete;
};
#endif //TOYHTTPD_BLOCKINGQUEUE_HPP
