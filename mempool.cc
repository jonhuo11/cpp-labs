#include <iostream>
#include <new>
#include <concepts>

using namespace std;

// memory pool for one type of object
template <typename T>
class MemPool {
    
    size_t size_in_bytes;
    void * pool_ptr;
    vector<bool> slot_states;
    
  public:
    MemPool(size_t size_in_bytes): size_in_bytes(size_in_bytes) {
        pool_ptr = malloc(size_in_bytes);
        if (pool_ptr == nullptr) {
            throw bad_alloc();
        }

        // calculate the number of slots
        slot_states.resize(size_in_bytes / sizeof(T), false);
    }

    ~MemPool() {
        for (unsigned int i = 0; i < slot_states.size(); i++) {
            if (slot_states[i]) {
                delete static_cast<T*>(get_slot(i));
            }
        }

        free(pool_ptr);
    }

    // returns index of the allocated object
    template <typename... Args>
    unsigned int alloc_new(Args&&... args) {
        // find first free slot
        int i = 0;
        for (; i < slot_states.size(); i++) {
            if (!slot_states[i]) {
                break;
            }
        }
        
        if (i >= slot_states.size()) {
            throw bad_alloc();
        }
        
        slot_states[i] = true;
        T * new_obj = new (get_slot(i)) T(forward<Args>(args)...);
        return i;
    }

    T& get_obj(unsigned int index) {
        if (!is_slot_valid(index)) {
            throw out_of_range("memory pool slot index out of bounds");
        }
        if (!slot_states[index]) {
            throw runtime_error("memory pool slot not allocated");
        }
        return *static_cast<T*>(get_slot(index));
    }

    void free_obj(unsigned int index) {
        if (!is_slot_valid(index)) {
            throw out_of_range("memory pool slot index out of bounds");
        }
        delete static_cast<T*>(get_slot(index));
        slot_states[index] = false;
    }

  private:
    bool is_slot_valid(unsigned int index) {
        return index < slot_states.size();
    }

    void * get_slot(unsigned char i) const {
        if (i >= slot_states.size()) {
            throw out_of_range("index out of memory pool slot range");
        }
        return static_cast<void*>(static_cast<char*>(pool_ptr) + i * sizeof(T));
    }
};