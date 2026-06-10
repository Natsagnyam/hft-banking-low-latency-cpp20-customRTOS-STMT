#pragma once
#include <cstdint>
#include <cstddef> // Required for size_t
#include <array>

namespace hft::engine {

    // Define these inside the namespace so they are visible to the pool
    static constexpr size_t PACKET_PAYLOAD_SIZE = 1024;
    static constexpr size_t POOL_SIZE = 65536; 

    struct Packet {
        uint8_t payload[PACKET_PAYLOAD_SIZE];
        uint32_t len;
        uint64_t timestamp;
    };

    class PacketPool {
    public:
        Packet& get(uint32_t index) {
            return pool[index & (POOL_SIZE - 1)];
        }

    private:
        std::array<Packet, POOL_SIZE> pool;
    };
}