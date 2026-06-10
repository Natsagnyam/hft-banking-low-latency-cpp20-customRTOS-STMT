#include "../include/control.hpp"
#include <iostream>
#include <cstdint>

int main() {
    // Use the namespace prefix since these structs are defined in hft::engine
    hft::engine::producer_ctrl p;
    hft::engine::consumer_ctrl c;

    uintptr_t addr_p = reinterpret_cast<uintptr_t>(&p);
    uintptr_t addr_c = reinterpret_cast<uintptr_t>(&c);

    std::cout << "Producer Address: " << addr_p << std::endl;
    std::cout << "Consumer Address: " << addr_c << std::endl;
    
    // Check if they are on the same cache line (assuming 64 bytes)
    if ((addr_p / 64) == (addr_c / 64)) {
        std::cout << "FAIL: False sharing detected!" << std::endl;
    } else {
        std::cout << "SUCCESS: Structures isolated." << std::endl;
    }

    return 0;
}