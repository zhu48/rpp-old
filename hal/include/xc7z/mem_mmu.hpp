#ifndef MEM_MMU_HPP
#define MEM_MMU_HPP

#include <cstdint>

#include "mem_load.h"

namespace mmu {

    enum class ttbr0_bit : std::uint32_t {
        inner_write_back = 1 << 6,
        outer_no_alloc   = 1 << 4,
        outer_write_back = 1 << 3,
        shareable        = 1 << 1,
        inner_no_alloc   = 1 << 0
    };

    constexpr std::uintptr_t l1_table_base        = PGRAM_BASE;
    constexpr std::size_t    l1_section_size      =  0x00100000;
    constexpr std::uint32_t  l1_table_num_entries = 0x100000000 / l1_section_size;
    constexpr std::size_t    l1_table_entry_size  = sizeof(std::size_t);
    constexpr std::size_t    l1_table_size        = l1_table_num_entries * l1_table_entry_size;

    constexpr std::uintptr_t l2_table_base             = l1_table_base + l1_table_size;
    constexpr std::size_t    l2_table_4k_section_size  = 0x00001000;
    constexpr std::size_t    l2_table_64k_section_size = 0x00010000;

}

#endif // #ifndef MEM_MMU_HPP
