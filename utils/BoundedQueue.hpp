#ifndef UTILS_BOUNDED_QUEUE_HPP
#define UTILS_BOUNDED_QUEUE_HPP

template<typename T>
class BoundedQueue {
public:
    void push(const T& t) {
        assert(!full());
        buff_[tail_] = t;
        tail_ = (tail_ + 1 % capacity_);
        size_++;
    }

    T pop() {
        assert(!empty());
        size_t oldHead = head_;
        head_ = (head_ + 1) % capacity_;
        size_--;
        return buff_[oldHead];
    }

    void clear() {
        head_ = 0;
        tail_ = 0;
        size_ = 0;
    }
    bool empty() const {
        return size_ == 0;
    }

    bool full() const {
        return capacity_ == size_;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    explicit BoundedQueue(size_t capacity) :
            capacity_(capacity), buff_(capacity),
            head_(0), tail_(0), size_(0) {}

    explicit BoundedQueue(const BoundedQueue& other) :
            head_(other.head_), tail_(other.tail_),
            size_(other.size_), capacity_(other.capacity_),
            buff_(other.buff_) {}

    explicit BoundedQueue(BoundedQueue&& other) :
            head_(other.head_), tail_(other.tail_),
            size_(other.size_), capacity_(other.capacity_),
            buff_(move(other.buff_)) {}

    BoundedQueue& operator= (BoundedQueue&& other) {
        assert(capacity_ == other.capacity_);

        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        buff_ = move(other.buff_);

        return *this;
    }

    BoundedQueue& operator= (const BoundedQueue& other) {
        assert(capacity_ == other.capacity_);

        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        buff_ = other.buff_;

        return *this;
    }
private:
    size_t head_;
    size_t tail_;
    size_t size_;
    const size_t capacity_;
    vector<T> buff_;
};




#endif