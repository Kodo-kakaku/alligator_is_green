#pragma once

#include <memory>
#include <array>

template<typename T, size_t BufferSize>
struct alligator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = alligator<U, BufferSize>;
    };

    explicit alligator(): alligator_index(0) {};
    ~alligator() = default;

    template<typename U>
    alligator(const alligator<U, BufferSize>&) {

    }

    pointer allocate(size_t n) {
        if (n == 0) // nothing to allocate
            return nullptr;
        if (alligator_index + n > BufferSize)
            throw std::bad_alloc();

        pointer current_pointer = &alligator_memory[alligator_index];
        alligator_index += n;
        return current_pointer;
    }

    void deallocate(pointer p, size_t n) {
        alligator_index -= n;
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args){
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }

private:
    std::array<value_type, BufferSize> alligator_memory;
    size_t alligator_index = 0;
};