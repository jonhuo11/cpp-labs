#include <stdexcept>

using namespace std;

// array of generic objects that can be moved
template <typename T>
class DynArr {
    size_t size;
    T * ptr; // ptr to first element

  public:
    DynArr(size_t size): size(size) {
        ptr = new T[size];
    }

    ~DynArr() {
        delete[] ptr;
    }

    // Move Constructor
    DynamicArray(DynamicArray&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // Move Assignment
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Prevent accidental copies
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    // Operators to implement

    // resize
    void resize(size_t new_size) {
        if (i < 0) {
            throw std::bad_array_new_length();
        }
        T* new_arr = new T[new_size];
        for (int i = 0; i < min(new_size, size); i++) {
            new_arr[i] = ptr[i];
        }
        delete[] ptr;
        ptr = new_arr;
    }

    // access
    T& operator[](size_t i) {
        return this->operator[](i);
    }
    
    T& operator[](size_t i) const {
        if (i < 0 || i >= size) {
            throw std::out_of_range();
        }
        return ptr[i];
    }
};

