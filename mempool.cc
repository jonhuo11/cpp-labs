#include <iostream>

using namespace std;


class MemPool {
    size_t size_in_bytes;
    void * pool_ptr;
  public:
    MemPool(size_t size_in_bytes): size_in_bytes(size_in_bytes) {
        void * pool_ptr = malloc(size_in_bytes);
    }

    ~MemPool() {
        free(pool_ptr);
    }

    void * allocNew() {
        
    }
};