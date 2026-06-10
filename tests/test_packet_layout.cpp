#include <iostream>
#include <cstddef> // Required for offsetof
#include "../include/hft_types.hpp" // Or whichever file contains the struct

int main() {
    using namespace hft::engine;

    std::cout << "Size of packet: " << sizeof(network_packet_t) << " bytes" << std::endl;
    std::cout << "Offset of ether_type: " << offsetof(network_packet_t, ether_type) << " bytes" << std::endl;
    std::cout << "Offset of payload:     " << offsetof(network_packet_t, payload) << " bytes" << std::endl;

    return 0;
}