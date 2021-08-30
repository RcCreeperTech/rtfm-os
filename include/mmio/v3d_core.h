#pragma once
#include "types.h"
#include "mmio/base.h"

typedef struct CacheRegs
{
  reg32 cache_control; // 0x20
  reg32 cache_control; // 0x24
  reg32 res_0[2]; // 0x28 - 0x2c
  reg32 t_cache_control; // 0x30
  reg32 t_flush_start; // 0x34
  reg32 t_flush_end; // 0x38
} CacheRegs;

typedef struct InterruptControlRegs
{
  reg32 status; // 0x50
  reg32 set; // 0x54
  reg32 clear; // 0x58
  reg32 mask_status; // 0x5c
  reg32 mask_set; // 0x60
  reg32 mask_clear; // 0x64
} InterruptControlRegs;


typedef struct CTPair
{
  reg32 reg[2];
} CTPair;

typedef struct CLERegs
{
  CTPair cs; // 0x100 - 0x104
  CTPair ea; // 0x108 - 0x10c
  CTPair ca; // 0x110 - 0x114
  CTPair ra; // 0x118 - 0x11c
  CTPair lc; // 0x120 - 0x124
  CTPair pc; // 0x128 - 0x12c
  reg32  pcs; // 0x130
  reg32  bfc; // 0x134
  reg32  rfc; // 0x138
  reg32  tfbc; // 0x13c
  reg32  tfit; // 0x140
  reg32  ct1_cgf; // 0x144
  reg32  ct1_tilect; // 0x148
  reg32  ct1_tskip; // 0x14c
  reg32  ct1_ptct; // 0x150
  CTPair sync; // 0x154 - 0x158
  reg32  ct0_qts; // 0x15c
  CTPair qba; // 0x160 - 0x164
  CTPair qea; // 0x168 - 0x16c
  reg32  ct0_qma; // 0x170
  reg32  ct0_qms; // 0x174
  reg32  ct1_q_cfg; // 0x178
} CLERegs;

typedef struct PTBRegs
{
  reg32 bpca; // 0x300
  reg32 bpcs; // 0x304
  reg32 bpoa; // 0x308
  reg32 bpos; // 0x30c
  reg32 bxcf; // 0x310
} PTBRegs;

typedef struct GMPRegs
{
  reg32 status; // 0x800
  reg32 config; // 0x804
  reg32 vio_address; // 0x808
  reg32 vio_type; // 0x80c
  reg32 table_address; // 0x810
  reg32 clear_load; // 0x814
  reg32 perserve_load; // 0x818
  reg32 valid_lines; // 0x820
} GMPRegs;

typedef struct ComputeShaderDispatchRegs
{
  reg32 status; // 0x900
  reg32 queued_cfg[7]; // 0x904 - 0x91c
    /* [4] Number of batches, minus 1 */
    /* [5] Shader address, pnan, singleseg, threading, like a shader record. */
    /* [6] Uniforms address (4 byte aligned) */
  reg32 current_cfg[7]; // 0x920 - 0x938
  reg32 current_id[2]; // 0x93c - 0x940

} ComputeShaderDispatchRegs;

typedef struct ErrorRegs
{
  reg32 fdbgo; // 0xf04
  reg32 fdbgb; // 0xf08
  reg32 fdbgr; // 0xf0c
  reg32 fdbgs; // 0xf10
  reg32 res_0[3]; // 0xf14 - 0xf1c
  reg32 stat; // 0xf20
} ErrorRegs;

typedef struct V3Regs
{
  reg32 res_0[2] // 0x650-0x654
  reg32 overflow; // 0x658
  reg8  src[2]; // 0x65c - 0x660
  reg32 res_2[3]; // 0x664 - 0x66c
  /* When a bit is set, resets the counter to 0. */
  reg32 clear; // 0x670
  reg32 enable; // 0x674
  reg32 res_3[3]; // 0x678 - 0x680
  /* Output values of the counters. */
  reg32 output[32]; // 0x684 - 0x704
} V3Regs;

typedef struct V4Regs
{
  reg32 enable; // 0x650
  reg32 clear; // 0x654
  reg32 overflow; // 0x658
  /* Each src reg muxes four counters each. */
  reg8  src[32]; // 0x65c - 0x67c
  reg32 output[32]; // 0x670 - 0x700
} V4Regs;

typedef struct CoreRegs
{
  reg32 ident[3]; // 0x0 - 0x08

  reg32 res_0[3]; // 0x0c - 0x14
  reg32 misc_config; // 0x18

  reg32 res_1; // 0x1c
  CacheRegs l2; // 0x20 - 0x38

  reg32 res_2[5]; // 0x3c - 0x4c
  InterruptControlRegs control_interrupt; // 0x50 - 0x64

  reg32 res_3[38]; // 0x68 - 0xfc
  CLERegs cle; // 0x100 - 0x178

  reg32 res_4[97]; // 0x17c - 0x2fc
  PTBRegs ptb; // 0x300 - 0x310

  reg32 res_5[207]; // 0x314 - 0x64c
  union 
  {
    V3Regs v3;
    V4Regs v4;
  } pctr;

  reg32 res_8[64]; // 0x700 - 0x7fc
  GMPRegs gmp; // 0x800 - 0x820

  reg32 res_9[55]; // 0x824 - 0x8fc
  ComputeShaderDispatchRegs csd; // 0x900 - 0x940

  reg32 res_10[368]; // 0x944 - 0xf00
  ErrorRegs err; // 0xf04 - 0xf20
} CoreRegs;

#define CORE_OFFSET(N)  0x8000 + (N * 4000)
#define REGS_V3D_CORE0 ((CoreRegs *)(V3D_BASE + CORE_OFFSET(0)))
#define REGS_V3D_CORE1 ((CoreRegs *)(V3D_BASE + CORE_OFFSET(1)))
#define REGS_V3D_CORE2 ((CoreRegs *)(V3D_BASE + CORE_OFFSET(2)))
#define REGS_V3D_CORE3 ((CoreRegs *)(V3D_BASE + CORE_OFFSET(3)))
