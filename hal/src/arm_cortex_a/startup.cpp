#include <cstdint>

#include <ARMCA9.h>

#include "mem_load.h"
#include "mmu.hpp"

extern int main( int argc, char* argv[] );

// Start and end points of the constructor list,
// defined by the linker script.
extern void ( *__init_array_start )();
extern void ( *__init_array_end )();

namespace {

    void construct_globals() {
        // Call each function in the list.
        // We have to take the address of the symbols, as __init_array_start *is* the first function
        // pointer, not the address of it.
        for ( void ( **p )() = &__init_array_start; p < &__init_array_end; ++p ) {
            ( *p )();
        }
    }

    void _start( void ) {
        construct_globals();
        main( 0, nullptr );
    }

    void create_tlb( void ) {
        mmu::generate_descriptors();

        mmu::fault_all();

        mmu::map_4k_x( EXROM_BASE, EXROM_LENG );
        mmu::map_4k_ro( DAROM_BASE, DAROM_LENG );
        mmu::map_4k_rw( DARAM_BASE, DARAM_LENG );
        mmu::map_4k_rw( PGRAM0_BASE, PGRAM0_LENG );
        mmu::map_4k_rw( PGRAM1_BASE, PGRAM1_LENG );

        mmu::commit_mappings();
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

        __set_SP( PGRAM1_END - 4 ); // initialize kernel stack before calling first possibly non-inline function

        // Initialize the memory system, including the MMU.
        L1C_DisableCaches();
        L1C_InvalidateBTAC();
        L1C_InvalidateICacheAll();
        L1C_CleanInvalidateDCacheAll();
        MMU_Disable();
        MMU_InvalidateTLB();

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
        while(true) {
            // spin
        }
    }

    extern "C" __attribute__ ((interrupt))
    void supervisor_call( void ) {
        while(true) {
            // spin
        }
    }

    extern "C" __attribute__ ((interrupt))
    void prefetch_abort( void ) {
        while(true) {
            // spin
        }
    }

    extern "C" __attribute__ ((interrupt))
    void data_abort( void ) {
        while(true) {
            // spin
        }
    }

    extern "C" __attribute__ ((interrupt))
    void interrupt_request( void ) {
        while(true) {
            // spin
        }
    }

    extern "C" __attribute__ ((interrupt))
    void fast_interrupt_request( void ) {
        while(true) {
            // spin
        }
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
