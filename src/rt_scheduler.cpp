#include "../include/rt_scheduler.hpp"
#include <x86intrin.h>

namespace hft::engine {
    // Define the global instance
    scheduler_ctrl g_scheduler;

    void init_scheduler() {
        g_scheduler.active_mask.store(0, std::memory_order_relaxed);
        for (int i = 0; i < MAX_TASKS; ++i) {
            g_scheduler.task_table[i].enabled = false;
            g_scheduler.task_table[i].task_func = nullptr;
        }
    }

        // 2. The Watchdog Task (to be registered in task_table)
    void watchdog_task() {
        uint64_t now = get_cycles();
        for (int i = 0; i < MAX_TASKS; ++i) {
            // If task is active but hasn't ticked in 50,000 cycles
            if ((g_scheduler.active_mask.load() & (1 << i)) && 
                (now - g_scheduler.last_heartbeat[i] > 50000)) {
                
                std::cerr << "WATCHDOG ALERT: Task " << i << " is starving!" << std::endl;
                // Handle error (e.g., reset task, emergency stop)
            }
        }
    }

    
    void run_scheduler() {
        while (true) {
            uint32_t mask = g_scheduler.active_mask.load(std::memory_order_acquire);
            
            if (mask == 0) {
                _mm_pause();
                continue;
            }

            for (int i = 0; i < MAX_TASKS; ++i) {
                if ((mask >> i) & 1) {
                    if (g_scheduler.task_table[i].enabled) {
                        g_scheduler.task_table[i].task_func();
                        
                        // Update heartbeat after successful execution
                        g_scheduler.last_heartbeat[i] = get_cycles();
                    }
                }
            }
            
            // --- Run Watchdog at the end of the loop ---
            watchdog_task();
        }
    }

}
