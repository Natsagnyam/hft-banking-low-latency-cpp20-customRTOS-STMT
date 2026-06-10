#pragma once
#include <cstdint>
#include <atomic>
#include <x86intrin.h>
#include <sched.h>
#include <pthread.h>
#include <iostream>

namespace hft::engine {

    static constexpr size_t MAX_TASKS = 8;

    struct task_t {
        void (*task_func)();
        uint32_t priority;
        bool enabled;
    };
    
    // 1. Update your scheduler_ctrl
    struct alignas(64) scheduler_ctrl {
        task_t task_table[MAX_TASKS];
        std::atomic<uint32_t> active_mask{0};
        uint64_t last_heartbeat[MAX_TASKS]; // Tracks time of last execution
    };



    // --- RT Helpers ---
    inline void set_realtime_priority() {
        struct sched_param param;
        param.sched_priority = 99;
        if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
            std::cerr << "WARNING: Failed to set SCHED_FIFO." << std::endl;
        }
    }

    inline void pin_thread_to_core(int core_id) {
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(core_id, &cpuset);
        pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    }
}