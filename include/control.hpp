#pragma once
#include <cstdint>
#include <atomic>

namespace hft::engine { // Must be inside the same namespace!

    struct producer_ctrl {
        uint8_t pad1[124];
        std::atomic<uint32_t> tail;
        uint8_t pad2[124];
    } __attribute__((aligned(64)));

    struct consumer_ctrl {
        uint8_t pad1[124];
        std::atomic<uint32_t> head;
        uint8_t pad2[124];
    } __attribute__((aligned(64)));

} // namespace hft::engine