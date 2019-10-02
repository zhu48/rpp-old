#include <cstddef>
#include <cstdint>

#include <ARMCA9.h>

#include "mem_mmu.hpp"
#include "mem_load.h"

extern int main( int argc, char* argv[] );

namespace {

    std::uint32_t mmu_section_normal;
    std::uint32_t mmu_section_normal_nc;
    std::uint32_t mmu_section_normal_cod;
    std::uint32_t mmu_section_normal_ro;
    std::uint32_t mmu_section_normal_rw;
    std::uint32_t mmu_section_so;
    std::uint32_t mmu_section_device_ro;
    std::uint32_t mmu_section_device_rw;
    std::uint32_t mmu_page4k_normal_cod_l1;
    std::uint32_t mmu_page4k_normal_cod_l2;
    std::uint32_t mmu_page4k_normal_ro_l1;
    std::uint32_t mmu_page4k_normal_ro_l2;
    std::uint32_t mmu_page4k_normal_rw_l1;
    std::uint32_t mmu_page4k_normal_rw_l2;
    std::uint32_t mmu_page4k_device_rw_l1;
    std::uint32_t mmu_page4k_device_rw_l2;
    std::uint32_t mmu_page64k_device_rw_l1;
    std::uint32_t mmu_page64k_device_rw_l2;

    void page4k_normal_cod(
        std::uint32_t&              descriptor_l1,
        std::uint32_t&              descriptor_l2,
        mmu_region_attributes_Type& region
    ) {
        region.rg_t         = mmu_region_size_Type::PAGE_4k;
        region.domain       = 0x0;
        region.e_t          = mmu_ecc_check_Type::ECC_DISABLED;
        region.g_t          = mmu_global_Type::GLOBAL;
        region.inner_norm_t = mmu_cacheability_Type::WB_WA;
        region.outer_norm_t = mmu_cacheability_Type::WB_WA;
        region.mem_t        = mmu_memory_Type::NORMAL;
        region.sec_t        = mmu_secure_Type::SECURE;
        region.xn_t         = mmu_execute_Type::EXECUTE;
        region.priv_t       = mmu_access_Type::READ;
        region.user_t       = mmu_access_Type::READ;
        region.sh_t         = mmu_shared_Type::NON_SHARED;
        MMU_GetPageDescriptor( &descriptor_l1, &descriptor_l2, region );
    }

    void page4k_normal_ro(
        std::uint32_t&              descriptor_l1,
        std::uint32_t&              descriptor_l2,
        mmu_region_attributes_Type& region
    ) {
        region.rg_t         = mmu_region_size_Type::PAGE_4k;
        region.domain       = 0x0;
        region.e_t          = mmu_ecc_check_Type::ECC_DISABLED;
        region.g_t          = mmu_global_Type::GLOBAL;
        region.inner_norm_t = mmu_cacheability_Type::WB_WA;
        region.outer_norm_t = mmu_cacheability_Type::WB_WA;
        region.mem_t        = mmu_memory_Type::NORMAL;
        region.sec_t        = mmu_secure_Type::SECURE;
        region.xn_t         = mmu_execute_Type::NON_EXECUTE;
        region.priv_t       = mmu_access_Type::READ;
        region.user_t       = mmu_access_Type::READ;
        region.sh_t         = mmu_shared_Type::NON_SHARED;
        MMU_GetPageDescriptor( &descriptor_l1, &descriptor_l2, region );
    }

    void page4k_normal_rw(
        std::uint32_t&              descriptor_l1,
        std::uint32_t&              descriptor_l2,
        mmu_region_attributes_Type& region
    ) {
        region.rg_t         = mmu_region_size_Type::PAGE_4k;
        region.domain       = 0x0;
        region.e_t          = mmu_ecc_check_Type::ECC_DISABLED;
        region.g_t          = mmu_global_Type::GLOBAL;
        region.inner_norm_t = mmu_cacheability_Type::WB_WA;
        region.outer_norm_t = mmu_cacheability_Type::WB_WA;
        region.mem_t        = mmu_memory_Type::NORMAL;
        region.sec_t        = mmu_secure_Type::SECURE;
        region.xn_t         = mmu_execute_Type::NON_EXECUTE;
        region.priv_t       = mmu_access_Type::RW;
        region.user_t       = mmu_access_Type::RW;
        region.sh_t         = mmu_shared_Type::NON_SHARED;
        MMU_GetPageDescriptor( &descriptor_l1, &descriptor_l2, region );
    }

    void _start( void ) {
        main( 0, NULL );
    }

    void create_mmu_handles( void ) {
        mmu_region_attributes_Type region;

        section_normal( mmu_section_normal, region );
        section_normal_nc( mmu_section_normal_nc, region );
        section_normal_cod( mmu_section_normal_cod, region );
        section_normal_ro( mmu_section_normal_ro, region );
        section_normal_rw( mmu_section_normal_rw, region );
        section_so( mmu_section_so, region );
        section_device_ro( mmu_section_device_ro, region );
        section_device_rw( mmu_section_device_rw, region );
        page4k_normal_cod( mmu_page4k_normal_cod_l1, mmu_page4k_normal_cod_l2, region );
        page4k_normal_ro( mmu_page4k_normal_ro_l1, mmu_page4k_normal_ro_l2, region );
        page4k_normal_rw( mmu_page4k_normal_rw_l1, mmu_page4k_normal_rw_l2, region );
        page4k_device_rw( mmu_page4k_device_rw_l1, mmu_page4k_device_rw_l2, region );
        page64k_device_rw( mmu_page64k_device_rw_l1, mmu_page64k_device_rw_l2, region );
    }

    void create_tlb( void ) {
        MMU_TTSection(
            reinterpret_cast<std::uint32_t*>( mmu::l1_table_base ),
            0,
            mmu::l1_table_num_entries,
            DESCRIPTOR_FAULT
        );

        MMU_TTPage4k(
            reinterpret_cast<std::uint32_t*>( mmu::l1_table_base ),
            EXROM_BASE,
            EXROM_LENG / mmu::l2_table_4k_section_size,
            mmu_page4k_normal_cod_l1,
            reinterpret_cast<std::uint32_t*>( mmu::l2_table_base ),
            mmu_page4k_normal_cod_l2
        );
        MMU_TTPage4k(
            reinterpret_cast<std::uint32_t*>( mmu::l1_table_base ),
            DAROM_BASE,
            DAROM_LENG / mmu::l2_table_4k_section_size,
            mmu_page4k_normal_ro_l1,
            reinterpret_cast<std::uint32_t*>( mmu::l2_table_base ),
            mmu_page4k_normal_ro_l2
        );
        MMU_TTPage4k(
            reinterpret_cast<std::uint32_t*>( mmu::l1_table_base ),
            DARAM_BASE,
            DARAM_LENG / mmu::l2_table_4k_section_size,
            mmu_page4k_normal_rw_l1,
            reinterpret_cast<std::uint32_t*>( mmu::l2_table_base ),
            mmu_page4k_normal_rw_l2
        );
    }

    extern "C" __attribute__ ((naked))
    void reset( void ) {
        // In a multi-core system, enable non-primary cores to sleep.
        __asm__ volatile(
            // disable all interrupts
            "    CPSID if                    \n" // disable all IRQ and FIQ interrupts
            // if this is not core zero, sleep until an interrupt makes this core do something
            "    MRC   p15, 0, R0, c0, c0, 5 \n" // read Multiprocessor Affinity Register into R0
            "    ANDS  R0, R0, #3            \n" // mask lowest two bits, which contain the core ID
            "sleep:                          \n"
            "    WFINE                       \n" // if not core zero, sleep until interrupted
            "    BNE   sleep                 \n" // stay asleep until a handler re-directs the core
        );

        // Initialize the memory system, including the MMU.
        L1C_DisableCaches();
        L1C_InvalidateBTAC();
        L1C_InvalidateICacheAll();
        L1C_CleanInvalidateDCacheAll();
        MMU_Disable();
        MMU_InvalidateTLB();

        __set_SP( PGRAM_END - 4 ); // initialize kernel stack before calling first possibly non-inline function

        create_mmu_handles();
        create_tlb();

        // Initialize core mode stacks and registers.
        // Initialize any critical I/O devices.

        // Perform any necessary initialization of NEON or VFP.
        __FPU_Enable();

        // Enable interrupts.
        // Change core mode or state.
        // Handle any set-up required for the Secure world.

        // Call the main() application.
        _start();
    }

    extern "C" __attribute__ ((interrupt))
    void undefined_instruction( void ) {
        
    }

    extern "C" __attribute__ ((interrupt))
    void supervisor_call( void ) {
        
    }

    extern "C" __attribute__ ((interrupt))
    void prefetch_abort( void ) {
        
    }

    extern "C" __attribute__ ((interrupt))
    void data_abort( void ) {
        
    }

    extern "C" __attribute__ ((interrupt))
    void interrupt_request( void ) {
        
    }

    extern "C" __attribute__ ((interrupt))
    void fast_interrupt_request( void ) {
        
    }

    extern "C" __attribute__ ((naked,__section__(".reset_table")))
    void exception_vector_table( void ) {
        __asm__ volatile(
            "B   reset                  \n" // branch to reset handler
            "B   undefined_instruction  \n" // branch to undefined instruction trap handler
            "B   supervisor_call        \n" // branch to supervisor call handler
            "B   prefetch_abort         \n" // branch to prefetch abort handler
            "B   data_abort             \n" // branch to data abort handler
            "NOP                        \n"
            "B   interrupt_request      \n" // branch to IRQ handler
            "B   fast_interrupt_request \n" // branch to FIQ handler
        );
    }

}
