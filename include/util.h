#pragma once
#include "types.h"

extern void write32(u64, u32);
extern u32  read32(u64);

extern int get_el();
extern void delay(u64 cycles);
