#pragma once
#include "types.h"
#include "mmio/base.h"

typedef struct VCMailboxRegs
{
  reg32 read;
  reg32 reserved[3];
  reg32 poll;
  reg32 sender;
  reg32 status;
  reg32 config;
  reg32 write;
} VCMailboxRegs;

#define VC_MBOX_OFFSET 0xB880
#define REGS_VC_MBOX ((VCMailboxRegs *)(PERIPHERAL_BASE + VC_MBOX_OFFSET))
