#ifndef MEM_CPU_HPP
#define MEM_CPU_HPP

#include <cstdint>

namespace platform {

    constexpr std::uintptr_t intercnx_cfg_gpv_base = 0xF8900000;
    constexpr std::uintptr_t scu_base              = 0xF8F00000;
    constexpr std::uintptr_t int_ctrl_base         = 0xF8F00100;
    constexpr std::uintptr_t global_timer_base     = 0xF8F00200;
    constexpr std::uintptr_t priv_timer_base       = 0xF8F00600;
    constexpr std::uintptr_t int_ctrl_dist_base    = 0xF8F01000;
    constexpr std::uintptr_t l2c_base              = 0xF8F02000;

}

#endif // #ifndef MEM_CPU_HPP
