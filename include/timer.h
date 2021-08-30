#pragma once
#include "mmio/timer.h"

#define TIMER_CS_M0 (1 << 0)
#define TIMER_CS_M1 (1 << 1)
#define TIMER_CS_M2 (1 << 2)
#define TIMER_CS_M3 (1 << 3)


void timer_init();
void handle_timer1();
void handle_timer3();

u64 timer_get_ticks();
void timer_sleep(u32 ms);
