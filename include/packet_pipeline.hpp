#pragma once
#include "packet_pool.hpp"
#include "control.hpp" // This MUST define producer_ctrl and consumer_ctrl
#include <cstdint>
#include <cstddef>

namespace hft::engine {
    extern PacketPool global_pool;
    extern producer_ctrl p_ctrl;
    extern consumer_ctrl c_ctrl;

    void produce(const uint8_t* raw_data, size_t len);
    void consume();
    void process_trade(const void* trade);
}