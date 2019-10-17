#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>

#include "cpu.h"

namespace platform {

    constexpr std::uintptr_t intercnx_cfg_gpv_base = 0xF8900000;
    constexpr std::uintptr_t scu_base              = 0xF8F00000;
    constexpr std::uintptr_t int_ctrl_base         = GIC_INTERFACE_BASE;
    constexpr std::uintptr_t global_timer_base     = 0xF8F00200;
    constexpr std::uintptr_t priv_timer_base       = TIMER_BASE;
    constexpr std::uintptr_t int_ctrl_dist_base    = GIC_DISTRIBUTOR_BASE;
    constexpr std::uintptr_t l2c_base              = L2C_310_BASE;

    std::uint32_t core_freq_hz();

}

#endif // #ifndef CPU_HPP
