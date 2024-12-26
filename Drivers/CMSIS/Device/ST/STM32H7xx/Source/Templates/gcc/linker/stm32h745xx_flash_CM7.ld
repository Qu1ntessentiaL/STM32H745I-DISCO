/*
******************************************************************************
**

**  File        : LinkerScript.ld
**
**
**  Abstract    : Linker script for STM32H7 series
**                1024Kbytes FLASH and 192Kbytes RAM
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
******************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = 0x20020000;    /* End of SRAM */
/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x2000;      /* Required amount of heap  */
_Min_Stack_Size = 0x4000;     /* Required amount of stack */

/* Specify the memory areas */
MEMORY
{
  FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 1024K     /* Internal Flash */
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 128K      /* Internal SRAM1 */
  ITCMRAM (xrw)   : ORIGIN = 0x00000000, LENGTH = 64K       /* ITCM RAM */
  QSPI (rx)       : ORIGIN = 0x90000000, LENGTH = 64M       /* External QSPI Flash */
  SDRAM (xrw)     : ORIGIN = 0xD0000000, LENGTH = 16M       /* External SDRAM */
}

/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* Program code and other data into FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* Define global symbol at the end of code */
  } >FLASH

  /* Constant data into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  /* Additional ARM-specific sections */
  .ARM.extab (READONLY) :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } >FLASH

  .ARM (READONLY) :
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  /* Initialization and finalization arrays */
  .preinit_array (READONLY) :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH

  .init_array (READONLY) :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH

  .fini_array (READONLY) :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* Data sections initialized in RAM with LMA in FLASH */
  _sidata = LOADADDR(.data);

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >RAM AT>FLASH

  /* Uninitialized data section */
  .bss :
  {
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  } >RAM

  /* Section for heap and stack */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

  /* External QSPI Flash section for code */
  .extflash_text :
  {
    . = ALIGN(4);
    *(.extflash_text)
    *(.extflash_text*)
    . = ALIGN(4);
  } >QSPI

  /* External SDRAM section for data */
  .sdram_data :
  {
    . = ALIGN(4);
    _ssdram = .;
    *(.sdram_data)
    *(.sdram_data*)
    . = ALIGN(4);
    _esdram = .;
  } >SDRAM AT>FLASH

  /* Optional: Logical separation of modules */
  .core :
  {
    . = ALIGN(4);
    *(.core)
    *(.core*)
    . = ALIGN(4);
  } >FLASH

  .modules :
  {
    . = ALIGN(4);
    *(.modules)
    *(.modules*)
    . = ALIGN(4);
  } >FLASH

  .resources :
  {
    . = ALIGN(4);
    *(.resources)
    *(.resources*)
    . = ALIGN(4);
  } >SDRAM AT>FLASH

  /* Discard unused sections */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
