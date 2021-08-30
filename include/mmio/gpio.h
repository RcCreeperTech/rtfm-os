#pragma once
#include "types.h"
#include "mmio/base.h"

typedef struct GpioPinData
{
  reg32 reserved;
  reg32 data[2];
} GpioPinData;

typedef struct GpioRegs
{
  reg32       function_select[6];
  GpioPinData output_set;
  GpioPinData output_clear;
  GpioPinData level;
  GpioPinData ev_detect_status;
  GpioPinData re_detect_enable;
  GpioPinData fe_detect_enable;
  GpioPinData hi_detect_enable;
  GpioPinData lo_detect_enable;
  GpioPinData async_re_detect;
  GpioPinData async_fe_detect;
  reg32       reserved;
  reg32       pupd[4];

} GpioRegs;

#define GPIO_OFFSET 0x200000
#define REGS_GPIO ((GpioRegs *)(PERIPHERAL_BASE + GPIO_OFFSET))
