MEMORY {
    FLASH  (rx) : ORIGIN = 0x08000000, LENGTH = 192K
    RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS {
    .text : { *(.text) }
}
