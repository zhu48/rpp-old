#ifndef MMU_HPP
#define MMU_HPP

#include <cstdint>

namespace mmu {

    void generate_descriptors( void );

    void commit_mappings( void );

    void fault_all( void );

    void map_section_fault( std::uintptr_t base, std::size_t length );

    void map_4k_x( std::uintptr_t base, std::size_t length );

    void map_4k_ro( std::uintptr_t base, std::size_t length );

    void map_4k_rw( std::uintptr_t base, std::size_t length );

    void map_64k_x( std::uintptr_t base, std::size_t length );

    void map_64k_ro( std::uintptr_t base, std::size_t length );

    void map_64k_rw( std::uintptr_t base, std::size_t length );

}

#endif // #ifndef MMU_HPP
