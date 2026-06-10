#include "../include/packet_pipeline.hpp"
#include <cstring>
#include <algorithm>
#include <atomic>

namespace hft::engine {
    // Define the global instances exactly once
    PacketPool global_pool;
    producer_ctrl p_ctrl;
    consumer_ctrl c_ctrl;

    void produce(const uint8_t* raw_data, size_t len) {
        uint32_t current_tail = p_ctrl.tail.load(std::memory_order_relaxed);
        
        auto& packet = global_pool.get(current_tail);
        std::memcpy(packet.payload, raw_data, std::min(len, PACKET_PAYLOAD_SIZE));

        p_ctrl.tail.store((current_tail + 1) & (POOL_SIZE - 1), std::memory_order_release);
    }

    void consume() {
        uint32_t last_head = c_ctrl.head.load(std::memory_order_relaxed);
        while (true) {
            uint32_t current_tail = p_ctrl.tail.load(std::memory_order_acquire);
            if (current_tail != last_head) {
                // ... logic ...
                last_head = (last_head + 1) & (POOL_SIZE - 1);
                c_ctrl.head.store(last_head, std::memory_order_release);
            }
        }
    }
}