#pragma once

#include "types.h"
#include "mmio/gpio.h"

#define GF_INPUT  0b000
#define GF_OUTPUT 0b001
#define GF_ALT0   0b100
#define GF_ALT1   0b101
#define GF_ALT2   0b110
#define GF_ALT3   0b111
#define GF_ALT4   0b011
#define GF_ALT5   0b010

#define GP_FREE   0b00
#define GP_UP     0b01
#define GP_DOWN   0b10

#ifndef __ASSEMBLER__

// set gpio pin function
void  gpio_pin_set_func(u8 pin, u8 function);
void  gpio_pin_pupd(u8 pin, u8 function);
#endif
