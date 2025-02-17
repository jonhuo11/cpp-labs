
#include <mutex>
#include <queue>
#include <condition_variable>
#include <utility>

using namespace std;

/**
 * Producer/consume queue implementation
 */
 
template <typename T>
class ConcurrentSafeWorkQueue {
    queue<T> work_queue;
    const size_t max_queue_size;
    bool shutdown = false;

    mutex mt;
    condition_variable cv;

public:
    ConcurrentSafeWorkQueue(size_t size): max_queue_size(size) {
        
    }

    ~ConcurrentSafeWorkQueue() {
        shutdown_queue();
    }

    void shutdown_queue() {
        unique_lock<mutex> lock(mt);
        shutdown = true;
        lock.unlock();
        cv.notify_all();
    }

    /**
     * Moves work into the queue
     */
    void add_work(T&& work_unit) {
        unique_lock<mutex> lock(mt);
        cv.wait(lock, [this] {return shutdown || work_queue.size() < max_queue_size; });

        if (shutdown) { // dont add new work
            return;
        }

        work_queue.push(move(work_unit));

        lock.unlock();
        cv.notify_one();
    }

    void add_work(const T&) = delete; // explicitly delete the lvalue overload to force move semantics

    /**
     * Blocking function which accepts work
     * Moves ownership of the work to the caller
     */
    bool consume_work(T& target) {
        unique_lock<mutex> lock(mt);
        cv.wait(lock, [this] {return shutdown || work_queue.size() > 0; });

        if (shutdown && work_queue.empty()) {
            return false;
        }
        
        *target = move(work_queue.front());
        work_queue.pop();

        lock.unlock();
        cv.notify_one();
        
        return true;
    }

};

