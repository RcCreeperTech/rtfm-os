#pragma once
#include "types.h"
#include "mmio/base.h"

#define CLOCK_HZ 1000000

typedef struct TimerRegs
{
  reg32 control_status;
  reg32 clock_lo;
  reg32 clock_hi;
  reg32 compare[4];

} TimerRegs;

#define TIMER_OFFSET 0x3000

#define REGS_TIMER ((TimerRegs *)(PERIPHERAL_BASE + TIMER_OFFSET))
