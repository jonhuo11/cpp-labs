/**
 * Profile concurrent queue speed
 */

#include <thread>
#include "concurrentqueue.cc"

double perform_work(const int& work_unit) {
    return sqrt(work_unit);
}

void generate(ConcurrentSafeWorkQueue<int>& q) {
    for (int i = 0; i < 1000; i++) {
        q.add_work(i * 3.14);
    }
}

int main() {



}
