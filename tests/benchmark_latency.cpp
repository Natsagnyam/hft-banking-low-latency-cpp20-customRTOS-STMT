#include "../include/packet_pipeline.hpp"
#include <iostream>

int main() {
    // Access the namespace to use the types
    using namespace hft::engine;

    // Now these declarations will be recognized
    // Note: Do not declare 'extern' here; just use the ones defined in the pipeline
    
    // Example usage:
    // auto& packet = global_pool.get(0);
    
    std::cout << "Starting latency benchmark..." << std::endl;
    // ... your benchmark logic ...

    return 0;
}