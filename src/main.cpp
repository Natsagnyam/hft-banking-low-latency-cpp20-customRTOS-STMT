#include "../include/packet_pipeline.hpp"
#include "../include/scheduler.hpp"
#include <iostream>

// Access the namespace where our engine components live
using namespace hft::engine;

int main() {
    // 1. Initialize the scheduler
    init_scheduler();

    // 2. Configure the producer task
    // (Assuming scheduler is configured to point to these functions)
    g_scheduler.task_table[0] = {producer_task, 1, true};
    g_scheduler.task_table[1] = {consumer_task, 1, true};

    std::cout << "Starting HFT Banking Engine..." << std::endl;

    // 3. Run benchmarks
    run_latency_benchmark(1000000);

    // 4. Start the main processing loop
    run_scheduler();

    return 0;
}