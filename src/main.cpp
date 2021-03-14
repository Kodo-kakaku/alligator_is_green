#include "alligator.h"
#include "keeper.h"

#include <iostream>
#include <map>


int factorial(const int x) {
    return x == 0 ? 1 : x * factorial(x - 1);
}

int main() {

    constexpr size_t SIZE = 10;

    // Map with standard allocator and custom allocator
    std::map<int, int> classic_map;
    std::map<int, int, std::less<>, Alligator<std::pair<const int, int>, SIZE>> alligator_map;

    for (size_t i = 0; i < SIZE; ++i) {
        const int res = factorial(i);
        classic_map.emplace(i, res);
        alligator_map.emplace(i, res);
    }

    for (const auto& value : classic_map) {
        std::cout << value.first << " " << value.second << '\n';
    }
    for (const auto& value : alligator_map) {
        std::cout << value.first << " " << value.second << '\n';
    }

    // Custom container keeper with standard allocator and custom allocator
    Keeper<int> keeper_int;
    Keeper<int, Alligator<int, SIZE>> keeper_alligator;

    for (size_t i = 0; i < SIZE; ++i) {
        keeper_int.append(i);       // like python 0_0
        keeper_alligator.append(i); // like python 0_0
    }

    for(const auto &value : keeper_int) {
        std::cout << value << '\n';
    }
    for(const auto &value : keeper_alligator) {
        std::cout << value << '\n';
    }
    std::cout << std::endl;

    return 0;
}