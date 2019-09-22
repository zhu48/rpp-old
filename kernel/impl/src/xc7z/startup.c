void reset( void ) __attribute__ ((naked)) {
    __ASM volatile(
        // disable all interrupts
        "    CPSID if                    \n" // disable all IRQ and FIQ interrupts
        // if this is not core zero, sleep until an interrupt handler makes this core do something
        "    MRC   p15, 0, R0, c0, c0, 5 \n" // read the Multiprocessor Affinity Register into R0
        "    ANDS  R0, R0, #3            \n" // mask lowest two bits, which contain the core ID
        "sleep:                          \n"
        "    WFINE                       \n" // if this is not core zero, sleep until interrupted
        "    BNE   sleep                 \n" // keep sleeping until a handler re-directs this core
        // initialize memory system
    );
}

void undefined_instruction( void ) {

}

void supervisor_call( void ) {
    
}

void prefetch_abort( void ) {
    
}

void data_abort( void ) {
    
}

void interrupt_request( void ) {
    
}

void fast_interrupt_request( void ) {
    
}

void exception_vector_table( void ) __attribute__ ((naked)) {
    __ASM volatile(
        "B   reset                  \n"
        "B   undefined_instruction  \n"
        "B   supervisor_call        \n"
        "B   prefetch_abort         \n"
        "B   data_abort             \n"
        "NOP                        \n"
        "B   interrupt_request      \n"
        "B   fast_interrupt_request \n"
    );
}
