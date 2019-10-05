#include "mem_load.h"

MEMORY {
    EXROM  (x)  : ORIGIN = EXROM_BASE, LENGTH = EXROM_LENG
    DAROM  (r)  : ORIGIN = DAROM_BASE, LENGTH = DAROM_LENG
    DARAM  (rw) : ORIGIN = DARAM_BASE, LENGTH = DARAM_LENG
    PGRAM0 (rw) : ORIGIN = PGRAM0_BASE, LENGTH = PGRAM0_LENG
    PGRAM1 (rw) : ORIGIN = PGRAM1_BASE, LENGTH = PGRAM1_LENG
}

ENTRY(exception_vector_table)

SECTIONS {
    .reset : {
        *(.reset_table)
        KEEP(*(.reset_table))
    } > EXROM

    .text : {
        *(.text*)
    } > EXROM

    .ctors : {
        .*(SORT(.ctors*))
    } > EXROM
    
    .dtors : {
        .*(SORT(.dtors*))
    } > EXROM

    .init_array : {
        __init_array_start = .;
        KEEP (*(.init_array*))
        __init_array_end = .;
    } > EXROM

    .rodata : {
        *(.rodata*)
    } > DAROM

    .data : {
        *(.data*)
    } > DARAM

    .bss : {
        *(.bss*)
    } > DARAM
}
