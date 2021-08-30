#pragma once

// ============================================
// | SCTLR_EL1: System contorl register (EL1) |
// | Page 2654 AArch64 reference manual       |
// ============================================

#define SCTLR_RESERVED       (3 << 28) |\
                             (3 << 22) |\
                             (1 << 20) |\
                             (1 << 11)  // reserved regs enable 1 default
#define SCTLR_EE_ENDIANESS   (0 << 25)  // set the endianess of data accesses in the el1 mode to le
#define SCTLR_E0E_ENDIANESS  (0 << 24)  // set the endianess of data accesses in the el0 mode to le
#define SCTLR_I_CACHE        (1 << 12)  // enable the instruction cache
#define SCTLR_D_CACHE        (1 << 2)   // enable the data cache
#define SCTLR_MMU            (0 << 0)   // disable the MMU until i implement virtual memory

#define SCTLR_CONF (SCTLR_RESERVED      |\
                    SCTLR_EE_ENDIANESS  |\
                    SCTLR_E0E_ENDIANESS |\
                    SCTLR_I_CACHE       |\
                    SCTLR_D_CACHE       |\
                    SCTLR_MMU)

// ====================================================
// | HCR_EL2: Hypervisor configuration register (EL2) |
// | Page 2487 AArch64 reference manual               |
// ====================================================

#define HCR_RW             (1 << 31) // Set execution mode to 64 bit

#define HCR_CONF (HCR_RW)

// ================================================
// | SCR_EL3, Secure Configuration Register (EL3) |
// | Page 2648 of AArch64-Reference-Manual        |
// ================================================

#define SCR_RESERVED  (3 << 4)
#define SCR_RW        (1 << 10)
#define SCR_NS        (1 << 0)
#define SCR_CONF (SCR_RESERVED | SCR_RW | SCR_NS)

// ====================================================
// | SPSR_EL3: Saved program status register (EL2)    |
// | Page 389 AArch64 reference manual                |
// ====================================================

#define SPSR_MASK_ALL    (7 << 6) // disable/mask fiq irq and SError
#define SPSR_EL1h        (5 << 0) // set EL1 to use its default stack pointer

#define SPSR_CONF (SPSR_MASK_ALL | SPSR_EL1h)

