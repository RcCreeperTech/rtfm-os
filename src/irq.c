#include "irq.h"
#include "types.h"
#include "printf.h"
#include "timer.h"
#include "util.h"
#include "mmio/aux.h"
#include "framebuffer.h"

char * exception_errors[] = 
{
  "ERROR_EL1t_SYNC",
  "ERROR_EL1t_IRQ",
  "ERROR_EL1t_FIQ",
  "ERROR_EL1t_ERROR",
  "ERROR_EL1h_SYNC",
  "ERROR_EL1h_IRQ",
  "ERROR_EL1h_FIQ",
  "ERROR_EL1h_ERROR",
  "ERROR_EL0_64_SYNC",
  "ERROR_EL0_64_IRQ",
  "ERROR_EL0_64_FIQ",
  "ERROR_EL0_64_ERROR",
  "ERROR_EL0_32_SYNC",
  "ERROR_EL0_32_IRQ",
  "ERROR_EL0_32_FIQ",
  "ERROR_EL0_32_ERROR"
};

void show_exception_error(s32 type, u64 esr, u64 addr)
{
  printf("%s :: ESR [%X] ADDRESS [%X]\n", exception_errors[type], esr, addr);
}

//enable timer 1 irq for core 0 of the bcm2711
void enable_interrupt_controller()
{
  REGS_ARMC_IRQ->core0.set_enabled.reg[0] = (VC_IRQ_AUX           |
                                             VC_IRQ_SYSTEM_TIMER1 |
                                             VC_IRQ_SYSTEM_TIMER3);

  REGS_ARMC_IRQ->core0.set_enabled.reg[1] = (VC_IRQ_SMI);
#ifdef ADVLOGS
  printf("interrupt_controller_enabled");
#endif
}

static bool swap = 0;
static u32 off = 0;

void handle_el1h_irq()
{
  u32 irq0 = REGS_ARMC_IRQ->core0.pending.reg[0];
  u32 irq1 = REGS_ARMC_IRQ->core0.pending.reg[1];
  // this will miss when multiple events are pending at once
  // printf("HANDLER :: event recieved!\n");
  while(irq1)
  {
    if(irq1 & VC_IRQ_SMI)
    {
      irq1 &= ~(VC_IRQ_SMI);
      //start the next frame
      framebuffer_clear();
      if(off >= 300) swap = !swap;
      if(off <= 0) swap = !swap;
      if(swap)
      {
        off++;
      }
      else
      {
        off--;
      }
      for(u32 i = 0 + off; i < 100 + off; i++)
      for(u32 j = 0 + off; j < 100 + off; j++)
      {
        framebuffer_put_pixel(i, j, 0xFFFFFFFF >> i);
      }
      timer_sleep(14);
      framebuffer_swap();
      *((reg32 *)SMI_CS) = 0; // clear set flag
    }
  }

  while(irq0)
  {
    // printf("HANDLER :: starting scan\n");
    if(irq0 & VC_IRQ_SYSTEM_TIMER1)
    {
      // printf("HANDLER :: in timer\n");
      irq0 &= ~(VC_IRQ_SYSTEM_TIMER1);
      handle_timer1();
    }
    if(irq0 & VC_IRQ_SYSTEM_TIMER3)
    {
      // printf("HANDLER :: in timer\n");
      irq0 &= ~(VC_IRQ_SYSTEM_TIMER3);
      handle_timer3();
    }

    if(irq0 & VC_IRQ_AUX)
    {
      // printf("HANDLER :: in uart\n");
      irq0 &= ~(VC_IRQ_AUX);

      while(REGS_AUX->mu_interrupt_identify & 0b100) // can recv byte
        printf("UART Recv: %c\n", REGS_AUX->mu_io & 0xFF);
    }
  }
}
