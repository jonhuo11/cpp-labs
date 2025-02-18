/**
 * Trying out concurrent queue
 */

#include <thread>
#include <atomic>
#include <iostream>
#include <future>
#include <vector>
#include <csignal>
#include <cstdlib>
#include "concurrentqueue.cc"

using namespace std;

atomic<bool> worker_shutdown (false);
ConcurrentSafeWorkQueue<int> * q;

void signalHandler(int signum) {
    if (worker_shutdown.load()) {
        exit(signum);
    }
    worker_shutdown.store(true);
    q->shutdown_queue();
}

double perform_work(const int& work_unit) {
    return sqrt(work_unit);
}

int worker(ConcurrentSafeWorkQueue<int>& q) {
    int * work_unit = new int(0);
    int work_done = 0;
    while (!worker_shutdown.load()) {
        if (!q.consume_work(work_unit)) {
            break;
        }
        perform_work(*work_unit);
        work_done++;
    }
    delete work_unit;
    return work_done;
}

void generate(ConcurrentSafeWorkQueue<int>& q) {
    q.add_work(81);
}

int main() {
    signal(SIGINT, signalHandler);

    auto core_count = thread::hardware_concurrency();
    cout << "Core count: " << core_count << endl;

    q = new ConcurrentSafeWorkQueue<int> (1000);

    for (int i = 0; i < 500; i++) {
        generate(*q);
    }

    const unsigned int worker_count = 4;
    vector<future<int>> workers (worker_count);
    
    for (int i = 0; i < worker_count; i++) {
        workers[i] = async(launch::async, worker, ref(*q));
    }

    for (auto& worker_result : workers) {
        cout << worker_result.get() << endl;
    }
    delete q;
}
