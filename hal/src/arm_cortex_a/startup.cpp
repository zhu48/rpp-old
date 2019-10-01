#include <cstddef>

#include <ARMCA9.h>

extern int main( int argc, char* argv[] );

extern "C" __attribute__ ((naked)) void reset( void ) {
    // In a multi-core system, enable non-primary cores to sleep.
    __asm__ volatile(
        // disable all interrupts
        "    CPSID if                    \n" // disable all IRQ and FIQ interrupts
        // if this is not core zero, sleep until an interrupt handler makes this core do something
        "    MRC   p15, 0, R0, c0, c0, 5 \n" // read the Multiprocessor Affinity Register into R0
        "    ANDS  R0, R0, #3            \n" // mask lowest two bits, which contain the core ID
        "sleep:                          \n"
        "    WFINE                       \n" // if this is not core zero, sleep until interrupted
        "    BNE   sleep                 \n" // keep sleeping until a handler re-directs this core
    );

    // Initialize the memory system, including the MMU.
    L1C_DisableCaches();
    L1C_InvalidateBTAC();
    L1C_InvalidateICacheAll();
    L1C_CleanInvalidateDCacheAll();
    MMU_Disable();
    MMU_InvalidateTLB();

    // Initialize core mode stacks and registers.
    // Initialize any critical I/O devices.
    // Perform any necessary initialization of NEON or VFP.
    __FPU_Enable();

    // Enable interrupts.
    // Change core mode or state.
    // Handle any set-up required for the Secure world (see Chapter 21).
    // Call the main() application.
}

extern "C" __attribute__ ((interrupt)) void undefined_instruction( void ) {

}

extern "C" __attribute__ ((interrupt)) void supervisor_call( void ) {
    
}

extern "C" __attribute__ ((interrupt)) void prefetch_abort( void ) {
    
}

extern "C" __attribute__ ((interrupt)) void data_abort( void ) {
    
}

extern "C" __attribute__ ((interrupt)) void interrupt_request( void ) {
    
}

extern "C" __attribute__ ((interrupt)) void fast_interrupt_request( void ) {
    
}

extern "C" __attribute__ ((naked,__section__(".reset_table"))) void exception_vector_table( void ) {
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

void _start( void ) {
    main( 0, NULL );
}
