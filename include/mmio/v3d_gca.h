#pragma once
#include "types.h"
#include "mmio/base.h"

typedef struct GcaRegs
{
  reg32 cache_control; // 0xC
  reg32 res_0[40]; // 0x10 - 0xB0
  reg32 safe_shutdown;
  reg32 safe_shutdown_ack;
} GcaRegs;

#define GCA_OFFSET    0x4100 + 0xC
#define REGS_V3D_GCA ((GcaRegs *)(V3D_BASE + GCA_OFFSET))
