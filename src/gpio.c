#include "gpio.h"
#include "types.h"
#include "util.h"

void  gpio_pin_set_func(u8 pin, u8 function)
{
  u8 bit_start = (pin * 3) % 30; // mod is magic lol
  u8 reg = pin / 10; // 58 regs so vals are wrapped 0-5

  reg32 selector = REGS_GPIO->function_select[reg];
    selector &= ~(0b111 << bit_start); // set all pin bits to 0
    selector |=  (function << bit_start); // set the pins function
  REGS_GPIO->function_select[reg] = selector;
}

void  gpio_pin_pupd(u8 pin, u8 function)
{
  u8 bit_start = (pin * 2) % 32; // mod is magic lol
  u8 reg = pin / 16; // 58 regs so vals are wrapped 0-3

  REGS_GPIO->pupd[reg] = (function << bit_start);
  // unsure of necessity of delay dance for pi 4 so omitting 4 now

}
