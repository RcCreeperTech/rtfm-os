#include "sysregs.h"
#include "mm.h"

.section ".text.boot" // linker info

.global _start

_start:
// Check processor ID is zero (executing on main core), else hang
  mrs x1, mpidr_el1
  and x1, x1, #3
  cbz x1, master

halt:  
  wfe
  b halt

master:
  mov x3, x0

  /* Enable FP/SIMD */
	/* Bit 10 (TFP) is set to 0 */
	msr CPTR_EL3, xzr

  ldr x0, =SCTLR_CONF
  msr sctlr_el1, x0

  ldr x0, =HCR_CONF
  msr hcr_el2, x0

  ldr x0, =SCR_CONF
  msr scr_el3, x0

  ldr x0, =SPSR_CONF
  msr spsr_el3, x0

  adr x0, el1_entry
  msr elr_el3, x0

  eret

el1_entry:
// Set stack to start below our code
  mov   sp, #LOW_MEMORY

// Clean the BSS section
  ldr   x1, =__bss_start
  ldr   w2, =__bss_size
memzero: 
  str   xzr, [x1], #8
  sub   w2, w2, #1
  cbnz  w2, memzero         // Loop if non-zero

// Jump to our main() routine in C (make sure it doesn't return)
  bl main
  b halt
