#include "mini_uart.h"
#include "types.h"
#include "util.h"
#include "gpio.h"
#include "mmio/aux.h"

#define TXD 14
#define RXD 15


void uart_init()
{
  gpio_pin_set_func(TXD, GF_ALT5);
  gpio_pin_set_func(RXD, GF_ALT5);
  
  gpio_pin_pupd(TXD, GP_FREE);
  gpio_pin_pupd(RXD, GP_FREE);

  REGS_AUX->enables             = 1; // enable mini uart
  REGS_AUX->mu_extra_control    = 0;
  REGS_AUX->mu_interrupt_enable = 0b1101; //enable recv interrupt docs are wrong
  REGS_AUX->mu_line_control     = 0b11;
  REGS_AUX->mu_modem_control    = 0;
  REGS_AUX->mu_baudrate         = AUX_MU_BAUD(115200);
  REGS_AUX->mu_extra_control    = 0b11;
}

void uart_send(char c)
{
  if(c == '\n')
  {
    while(!(REGS_AUX->mu_line_status & 0x20));
    REGS_AUX->mu_io = '\r';
  }
  while(!(REGS_AUX->mu_line_status & 0x20));
  REGS_AUX->mu_io = c;
}

char uart_recv()
{
    while(!(REGS_AUX->mu_line_status & 0x01));
    return (char)REGS_AUX->mu_io;
}

void putchar(char c) {
  uart_send(c);
}
