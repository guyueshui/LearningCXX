/** @DESCRIPTION
 *	Implement a queue API using an array for storing elements. Your API should
 *	include a constructor function, which takes as argument the initial
 *	capacity of the queue, enqueue and dequeue functions, and a function which
 *	returns the number of elements stored. Implement dynamic resizing to
 *	support storing an arbitrarily large number of elements.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>    // std::rotate

using std::string;
using std::vector;

/************ begin ***************/
template <typename T>
class queue {
public:
    // given a queue with size c, it can actually store c-1 elems
    explicit queue(size_t capacity): _capacity(capacity) { 
        _data.resize(capacity - 1); // it can only store c-1 elems
    }
    void push(T e);
    T& pop(); 

    // some tools
    bool empty() { return _head == _tail; }
    bool full() { return (_tail + 1) % _capacity == _head; }
    size_t size() const {
        return (_tail + _capacity - _head) % _capacity;
    }
    void printer() {
        std::cout << "head <- ";
        for (auto pos = _head; pos != _tail; ++pos)
            std::cout << _data[pos] << " ";
        std::cout << "<- tail" << std::endl;
    }
private:
    // data members
    size_t _capacity = 0; 
    size_t _head = 0;       // head element index
    size_t _tail = 0;       // tail element index
    vector<T> _data;        // the array
}; // class queue

/* impl the custom queue */
// impl push
template <typename T> 
void queue<T>::push(T e) {
    if (!full()) { // if the queue is not full
        _data[_tail] = e;
        _tail = (_tail + 1) % _capacity;
    } else { // the queue is full, rearrange
        // left-shift by _head steps
        std::rotate(_data.begin(), _data.begin() + _head, _data.end());
        _data.push_back(e);
        _head = 0;
        _tail = _data.size();
        ++_capacity;
    }
}
// impl pop
template <typename T>
T& queue<T>::pop() {
    auto dummy_head = _head;
    _head = (_head + 1) % _capacity;
    return _data[dummy_head];
} 
/************ end ****************/

// epi solution
class Queue {
public:
    explicit Queue(size_t capacity) : entries_(capacity) { 
        entries_.resize(capacity);
    }

    void Enqueue(int x) {
        if (num_queue_elements == entries_.size()) { // Needs to resize
            // Make the queue elements appear consecutively
            std::rotate(entries_.begin(), entries_.begin() + head_, entries_.end());
            head_ = 0, tail_ = num_queue_elements; // Reset head and tail
            entries_.resize(entries_.size() * kScaleFactor);
        }
        entries_[tail_] = x;
        tail_ = (tail_ + 1) % entries_.size();
        ++num_queue_elements;
    }

    int Dequeue() {
        if (!num_queue_elements) {
            throw std::length_error("empty queue");
        }
        --num_queue_elements;
        int ret = entries_[head_];
        head_ = (head_ + 1) % entries_.size();
        return ret;
    }

    size_t size() const { return num_queue_elements; }

    void printer() {
        std::cout << "head <- ";
        for (auto pos = head_; pos != tail_; ++pos)
            std::cout << entries_[pos] << " ";
        std::cout << "<- tail" << std::endl;
    }

    void Test() {
        std::cout << "Here comes Test for Queue:\n";
        Queue q(5);
        int n = 4;
        while (n--) {
            q.Enqueue(n);
        }
        q.printer();
        q.Dequeue();
        q.printer();
        std::cout << "Ends Test!\n";
    }
private:
    const int kScaleFactor = 2;
    size_t head_ = 0, tail_ = 0, num_queue_elements = 0;
    vector<int> entries_;
};


// test
int main(int argc, char *argv[]) {
    self::queue<string> q(5); // it can only store 4 elems
    // fill the queue
    int n = 4;
    while (n--) {
        q.push("baby" + std::to_string(n));
    }
    q.printer();
    q.push("haha");
    q.printer();
    std::cout << q.pop() << std::endl;
    q.printer();
    std::cout << q.size();
    Queue qq(5);
    qq.Test();
    return 0;
}
