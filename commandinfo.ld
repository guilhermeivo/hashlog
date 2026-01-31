SECTIONS {
    .commandinfo : {
        __start_commandinfo = .;
        KEEP(*(.commandinfo))
        __stop_commandinfo = .;
    }
} INSERT AFTER .rodata;
