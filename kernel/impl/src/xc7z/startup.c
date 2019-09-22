void reset( void ) __attribute__ ((naked)) {

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
