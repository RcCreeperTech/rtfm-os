#pragma once
#include "types.h"
#include "mmio/base.h"

typedef struct BridgeRegs
{
  reg32 revision;
  reg32 res;
  reg32 sw_init[2];
} BridgeRegs;

#define BRIDGE_OFFSET 0x4000
#define REGS_V3D_BRIDGE ((BridgeRegs *)(V3D_BASE + BRIDGE_OFFSET))
