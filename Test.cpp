#include <cstdint>
#include <cstdio>
#include <immer/map.hpp>
#include <immer/map_transient.hpp>
#include <iostream>

int main() {
    immer::map<int, int> map;
    
    map = map.insert({1, 2});
    auto* iter = map.find(1);
    if (!iter) {
        std::cout << "not found" << std::endl;
    } else {
        std::cout << *iter << std::endl;
    }

    return 0;
}