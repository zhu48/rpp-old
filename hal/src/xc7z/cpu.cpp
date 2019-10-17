#include "ps7_init_gpl.h"

#include "cpu.hpp"

using namespace platform;

std::uint32_t core_freq_hz() {
    return APU_FREQ;
}
