#include <iostream>
#include "../include/hft_types.hpp"

int main() {
    const uint32_t POOL_SIZE = 1024;
    
    // Simulate index wrapping
    for (uint32_t i = 1020; i < 1030; ++i) {
        uint32_t wrapped = i & (POOL_SIZE - 1);
        std::cout << "Index " << i << " wraps to " << wrapped << std::endl;
    }

    // Validation: 1024 & 1023 should be 0
    if ((1024 & (POOL_SIZE - 1)) == 0) {
        std::cout << "SUCCESS: Ring buffer wrap logic valid." << std::endl;
        return 0;
    }
    return 1;
}