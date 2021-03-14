#pragma once
#include <memory>

template<typename T, typename Alloc = std::allocator<T>>
class Keeper {
public:
    using Allocat = typename Alloc::template rebind<T>::other;

    Keeper() {
        size_ = 0;
        hold_mem_ = 10;
        keeper_data_ = allocator.allocate(hold_mem_);
        end_ = keeper_data_;
    }

    explicit Keeper(size_t size) {
        size_ = size;
        hold_mem_ = 2 * size_;
        keeper_data_ = allocator.allocate(hold_mem_);
        end_ = keeper_data_ + size;
    }

    ~Keeper() {
        allocator.deallocate(keeper_data_, hold_mem_);
        hold_mem_ = 0;
        size_ = 0;
    }

    T &operator[](size_t index) {
        return *(keeper_data_ + index);
    }

    T *begin() {
        return keeper_data_;
    }

    T *end() {
        return end_;
    }

    const T *begin() const {
        return keeper_data_;
    }

    const T *end() const {
        return end_;
    }

    [[nodiscard]] size_t Size() const {
        return size_;
    }

    [[nodiscard]] size_t Capacity() const {
        return hold_mem_;
    }

    void append(const T &value);

private:
    T *keeper_data_;
    T *end_;
    size_t size_;
    size_t hold_mem_;
    Allocat allocator;
};

template<typename T, typename Allocator>
void Keeper<T, Allocator>::append(const T &value) {
    if (Size() >= Capacity()) {
        hold_mem_ != 0 ? hold_mem_ *= 2 : hold_mem_ = 2;
        T *ptr = allocator.allocate(hold_mem_);
        for (size_t i = 0; i < size_; ++i) {
            *ptr++ = *keeper_data_++;
        }
        allocator.deallocate(keeper_data_, hold_mem_);
        keeper_data_ = ptr;
        keeper_data_[size_++] = value;
        end_ = keeper_data_ + size_;
    } else {
        keeper_data_[size_++] = value;
        end_ = keeper_data_ + size_;
    }
};