#include "mem_load.h"

MEMORY {
    EXROM (x)  : ORIGIN = EXROM_BASE, LENGTH = EXROM_LENG
    DAROM (r)  : ORIGIN = DAROM_BASE, LENGTH = DAROM_LENG
    DARAM (rw) : ORIGIN = DARAM_BASE, LENGTH = DARAM_LENG
    PGRAM (rw) : ORIGIN = PGRAM_BASE, LENGTH = PGRAM_LENG
}

ENTRY(exception_vector_table)

SECTIONS {
    .reset : {
        *(.reset_table)
        KEEP(*(.reset_table))

        *(.text*)

        .*(SORT(.ctors*))
        .*(SORT(.dtors*))
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
