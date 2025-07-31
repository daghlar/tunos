SECTIONS
{
  . = SIZEOF_HEADERS;
  .text : { *(.text) }
  .rodata : { *(.rodata) }
  .data.rel.ro : { *(.data.rel.ro) }
  .data : { *(.data) }
  .bss : { *(.bss) }
  .got : { *(.got) }
  .got.plt : { *(.got.plt) }
} 