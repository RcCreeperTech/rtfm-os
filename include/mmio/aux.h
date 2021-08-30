#pragma once
#include "types.h"
#include "mmio/base.h"

// Registers controlling three auxiliary peripherals
// 1 mini-UART
// 2 SPI masters

typedef struct AuxRegs
{
  reg32 irq_status;
  reg32 enables;
  reg32 reserved[14];
  reg32 mu_io;
  reg32 mu_interrupt_enable;
  reg32 mu_interrupt_identify;
  reg32 mu_line_control;
  reg32 mu_modem_control;
  reg32 mu_line_status;
  reg32 mu_modem_status;
  reg32 mu_scratch;
  reg32 mu_extra_control;
  reg32 mu_extra_status;
  reg32 mu_baudrate;
  /* SPI interface unimplemented */
} AuxRegs;

#define AUX_OFFSET 0x215000
#define REGS_AUX ((AuxRegs *)(PERIPHERAL_BASE + AUX_OFFSET))

#define AUX_UART_CLOCK 500000000
#define AUX_MU_BAUD(baud) ((AUX_UART_CLOCK/(baud*8))-1)
