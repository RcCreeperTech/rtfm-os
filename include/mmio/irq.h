#pragma once
#include "mmio/base.h"

typedef struct ArmcIrqData
{
  reg32 reg[3];
  reg32 reserved;
} ArmcIrqData;

typedef struct ArmcIrqCore
{
  ArmcIrqData pending;
  ArmcIrqData set_enabled;
  ArmcIrqData clear_enabled;
} ArmcIrqCore;

typedef struct ArmcIrqRegs
{
  ArmcIrqCore core0;
  ArmcIrqData status; // unmasked status of all irq lines
  ArmcIrqCore core1;
  ArmcIrqCore core2;
  ArmcIrqCore core3;
  /* FIQ and vIrq unimplemented */
} ArmcIrqRegs;

#define ARMC_IRQ_OFFSET 0xB200

#define REGS_ARMC_IRQ ((ArmcIrqRegs *)(PERIPHERAL_BASE + ARMC_IRQ_OFFSET))

