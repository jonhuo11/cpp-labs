
// array of generic objects that can be moved
template <typename T>
class DynArr {
    size_t size;
    T * ptr; // ptr to first element

  public:
    DynArr(size_t size): size(size) {

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
    void resize(size_t size);

    // access
    T& operator[](size_t i) {

    }
    
    T& operator[](size_t i) const {

    }
};

