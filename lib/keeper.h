#pragma once

#include <memory>

template<typename T, typename t_alligator = std::allocator<T>>
class keeper {
public:
    struct keeper_elements {
        keeper_elements() = default;
        explicit keeper_elements(const T &value_) : value(value_), next(nullptr) {};

        T value;
        keeper_elements *next;
    };

    using Alloc = typename t_alligator::template rebind<keeper_elements>::other;

    keeper() = default;

    ~keeper() = default;

    void add_element(const T &value) {
        auto keep = list_allocator.allocate(1);
        keep->value = value;
        if (keep) {
            if (Head_) {
                Tail_->next = keep;
                Tail_ = keep;
            } else {
                Head_ = keep;
                Tail_ = keep;
            }
        }
    }

    class CustomListIterator {
    public:
        using value_type = keeper;
        using pointer = keeper *;
        using difference_type = int;

        CustomListIterator(keeper_elements *element) : current_element(element) {}

        CustomListIterator operator++() {
            current_element = current_element->next;
            return current_element;
        }

        decltype(auto) operator*() { return current_element->value; }

        bool operator==(const CustomListIterator &rhs) { return current_element == rhs.current_element; }

        bool operator!=(const CustomListIterator &rhs) { return current_element != rhs.current_element; }

    private:
        keeper_elements *current_element;
    };

    CustomListIterator begin() {
        return CustomListIterator(this->Head_);
    }

    CustomListIterator end() {
        if (Tail_)
            return CustomListIterator(this->Tail_->next);
        return CustomListIterator(nullptr);
    }

private:
    keeper_elements *Head_ = nullptr;
    keeper_elements *Tail_ = nullptr;
    Alloc list_allocator;
};