#include "alligator.h"
#include "keeper.h"

#include <iostream>
#include <map>


int factorial(const int x) {
    return x == 0 ? 1 : x * factorial(x - 1);
}

int main() {
    const unsigned SIZE = 10;
    // Map with standard allocator
    std::map<int, int> classic_map;
    auto alligator_map = std::map<int, int, std::less<>, alligator<std::pair<const int, int>, SIZE>> {};

    for (size_t i = 0; i < SIZE; ++i) {
        const int res = factorial(i);
        classic_map.try_emplace(i, res);
        alligator_map.try_emplace(i, res);
    }

    for(const auto& [key, value] : classic_map) {
        std::cout << key << " " << value << std::endl;
    }
    for(const auto& [key, value] : alligator_map) {
        std::cout << key << " " << value << std::endl;
    }

    // Custom container (List) with standard allocator
    keeper<int> keeper_int;
    keeper<int, alligator<int, SIZE>> keeper_alligator;

    for (size_t i = 0; i < SIZE; ++i) {
        keeper_int.add_element(i);
        keeper_alligator.add_element(i);
    }

    for (const auto& value: keeper_int) {
        std::cout << value << std::endl;
    }
    for (const auto& value: keeper_alligator) {
        std::cout << value << std::endl;
    }

    return 0;
}