#include <stdexcept>
#include <utility>

using namespace std;

// array of generic objects that can be moved
template <typename T>
class DynArr {
    size_t size;
    T * ptr; // ptr to first element

  public:
    DynArr(size_t size): size(size) {
        ptr = new T[size]();
    }

    ~DynArr() {
        delete[] ptr;
    }

    // Move Constructor
    DynArr(DynArr&& other) noexcept
        : size(other.size),  // Must come first due to member declaration order
          ptr(other.ptr) {
        other.ptr = nullptr;
        other.size = 0;
    }

    // Move Assignment
    DynArr& operator=(DynArr&& other) noexcept {
        if (this != &other) {
            delete[] ptr;
            ptr = other.ptr;
            size = other.size;
            other.ptr = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Prevent accidental copies
    DynArr(const DynArr&) = delete;
    DynArr& operator=(const DynArr&) = delete;

    // Operators to implement

    // resize
    void resize(size_t new_size) {
        T* new_arr = new T[new_size]();
        for (size_t i = 0; i < min(new_size, size); i++) {
            new_arr[i] = ptr[i];
        }
        delete[] ptr;
        size = new_size;
        ptr = new_arr;
    }

    // access
    T& operator[](size_t i) {
        if (i >= size) {
            throw out_of_range("Index out of bounds");
        }
        return ptr[i];
    }
    
    T& operator[](size_t i) const {
        if (i >= size) {
            throw out_of_range("Index out of bounds");
        }
        return ptr[i];
    }

    size_t getSize() const {
        return size;
    }
};

