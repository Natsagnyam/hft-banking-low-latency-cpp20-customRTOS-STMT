#pragma once
#include <cstdint>

namespace hft::engine {
    #pragma pack(push, 1)
    struct network_packet_t {
        uint8_t dest_mac[6];
        uint8_t src_mac[6];
        uint16_t ether_type;
        uint8_t payload[1024];
    };
    #pragma pack(pop)
}