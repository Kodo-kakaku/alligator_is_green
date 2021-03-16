#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>

template<typename T, size_t N>
struct Alligator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    template<typename U, size_t M = N>
    struct rebind {
        using other = Alligator<U, M>;
    };

    Alligator() : current_size_(0) {
        auto mem_buf = std::malloc(N * sizeof(T));
        if (!mem_buf) {
            std::bad_alloc();
        }
        data_ = reinterpret_cast<T*>(mem_buf);
    };

    ~Alligator() = default;

    Alligator(const Alligator &other) : data_(other.data_), current_size_(other.current_size_) {}

    T *allocate(std::size_t n) {
        if (current_size_ + n > max_size_) {
            std::bad_alloc();
        }
        auto cur_data = &data_[current_size_];
        current_size_ += n;
        if (!cur_data) {
            throw std::bad_alloc();
        }
        return reinterpret_cast<T*>(cur_data);
    }

    void deallocate(T *val, std::size_t n) {
        static_cast<void>(val);
        current_size_ -= n;
        if (current_size_ == 0) {
            std::free(data_);
        }
    }

    template<typename U, typename ...Args>
    void construct(U *val, Args &&...args) {
        new(val) U(std::forward<Args>(args)...);
    };

    template<typename U>
    void destroy(U *p) {
        p->~U();
    }

private:
    T *data_;
    size_t current_size_;
    size_t max_size_ = N;
};