#include "timer.h"
#include "types.h"
#include "printf.h"
#include "framebuffer.h"

u32 timestamp1 = 0;
u32 timestamp3 = 0;

#define INC60 CLOCK_HZ / 60

void timer_init()
{
  timestamp1 = REGS_TIMER->clock_lo;
  timestamp1 += INC60;
  REGS_TIMER->compare[1] = timestamp1;

  // timestamp3 = REGS_TIMER->clock_lo;
  // timestamp3 += CLOCK_HZ + 500000;
  // REGS_TIMER->compare[3] = timestamp3;
}

void handle_timer1()
{
  timestamp1 += INC60;
  REGS_TIMER->compare[1] = timestamp1;
  REGS_TIMER->control_status |= TIMER_CS_M1;

  // printf("Tick...\n");
}

void handle_timer3()
{
  timestamp3 += CLOCK_HZ;
  REGS_TIMER->compare[3] = timestamp3;
  REGS_TIMER->control_status |= TIMER_CS_M3;
  // printf("Tock...\n");
}

u64 timer_get_ticks()
{
  u32 c_hi = REGS_TIMER->clock_hi;
  u32 c_lo = REGS_TIMER->clock_lo;

  if(c_hi != REGS_TIMER->clock_hi)
  {
    c_hi = REGS_TIMER->clock_hi;
    c_lo = REGS_TIMER->clock_lo;
  }

  return ((u64)c_hi << 32) | c_lo;
}

//in milliseconds
void timer_sleep(u32 ms)
{
  u64 start = timer_get_ticks();

  while(timer_get_ticks() < start + (ms * 1000));
}
