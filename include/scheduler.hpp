#pragma once
#include "control.hpp"

namespace hft::engine {
    struct Scheduler {
        struct Task { void (*func)(); int priority; bool enabled; };
        Task task_table[10];
    };
    extern Scheduler g_scheduler;
    void init_scheduler();
    void run_scheduler();
    void run_latency_benchmark(int iterations);
    void producer_task();
    void consumer_task();
}