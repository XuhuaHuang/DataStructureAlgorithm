/*****************************************************************//**
 * \file   linear_vector.hpp
 * \brief  Linear vector with resizing policy implementation.
 *
 * TODO: pending refactoring and provide miscellaneous operators.
 *
 * \author Xuhua Huang
 * \date   March 25, 2023
 *********************************************************************/

template <typename T, size_t InitialCapacity = 8, typename ResizePolicy = DefaultResizePolicy>
struct LinearVector {
public:
    LinearVector() : size_(0), capacity_(InitialCapacity) {
        data_ = new T[capacity_];
    }

    LinearVector(const LinearVector<T, InitialCapacity, ResizePolicy>& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    ~LinearVector() {
        delete[] data_;
    }

    // Add an element to the end of the vector
    void push_back(const T& value) {
        if (size_ == capacity_) {
            resize();
        }
        data_[size_++] = value;
    }

    // Remove the last element from the vector
    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("vector is empty");
        }
        --size_;
    }

    // Get a reference to the element at the specified index
    T& operator[](const size_t index) {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return data_[index];
    }

    // Get a const reference to the element at the specified index
    const T& operator[](const size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return data_[index];
    }

    // Get the number of elements in the vector
    size_t size() const {
        return size_;
    }

    // Get the current capacity of the vector
    size_t capacity() const {
        return capacity_;
    }

    // Check if the vector is empty
    bool empty() const {
        return size_ == 0;
    }

private:
    T* data_;
    size_t size_;
    size_t capacity_;

    // Resize the vector using the ResizePolicy
    void resize() {
        ResizePolicy resize_policy;
        capacity_ = resize_policy(capacity_);
        T* new_data = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
};

// Default resizing policy doubles the capacity of the vector
struct DefaultResizePolicy {
    size_t operator()(const size_t current_capacity) const {
        return current_capacity * 2;
    }
};

// Resizing policy that increases the capacity of the vector by a fixed amount
struct FixedResizePolicy {
    FixedResizePolicy(const size_t increment) : increment_(increment) {}

    size_t operator()(const size_t current_capacity) const {
        return current_capacity + increment_;
    }

private:
    size_t increment_;
};
