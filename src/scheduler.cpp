#include "../include/scheduler.hpp"
#include <iostream>

namespace hft::engine {
    // Define the global instance
    Scheduler g_scheduler;

    void init_scheduler() {
        std::cout << "Scheduler initialized." << std::endl;
    }

    void producer_task() { /* Logic */ }
    void consumer_task() { /* Logic */ }

    void run_scheduler() {
        std::cout << "Scheduler running..." << std::endl;
    }

    void run_latency_benchmark(int iterations) {
        std::cout << "Running benchmark for " << iterations << " iterations." << std::endl;
    }
}


