#include "mini_uart.h"
#include "printf.h"
#include "util.h"
#include "irq.h"
#include "timer.h"
#include "banner.h"
#include "mailbox_prop.h"
#include "framebuffer.h"

#include "v3d_hub.h"
void main()
{
  uart_init();

  printf("\n");
  for(int i = 0; i < BANNER_LINES; i++) printf("%s", banner[i]);
  printf("Board Model: Raspberry PI4B 8GB\n");
  int exception_level = get_el();
  printf("The system's current exception level is: %d\n", exception_level);

  printf("V3D Revision: %d.%d.%d.%d\n", 
        (REGS_V3D_HUB->ident[1] & V3D_HUB_IDENT1_TVER_MASK)  >> V3D_HUB_IDENT1_TVER_SHIFT,
        (REGS_V3D_HUB->ident[1] & V3D_HUB_IDENT1_REV_MASK)   >> V3D_HUB_IDENT1_REV_SHIFT,
        (REGS_V3D_HUB->ident[3] & V3D_HUB_IDENT3_IPREV_MASK) >> V3D_HUB_IDENT3_IPREV_SHIFT,
        (REGS_V3D_HUB->ident[3] & V3D_HUB_IDENT3_IPIDX_MASK) >> V3D_HUB_IDENT3_IPIDX_SHIFT
        );

  mbox_prop_init();
    mbox_prop_add(TAG_GET_MAX_CLOCK_RATE, TAG_CLOCK_ARM);
  mbox_prop_call();

  MboxPropTag * prop = mbox_prop_get(TAG_GET_MAX_CLOCK_RATE);

  mbox_prop_init();
    mbox_prop_add(TAG_SET_CLOCK_RATE, TAG_CLOCK_ARM, prop->data.buffer_32[1]);
  mbox_prop_call();


  framebuffer_init();

  irq_vtable_init();
  enable_interrupt_controller();
  enable_irq();


  while(1)
  {
  }
}


// timer_init();
// mbox_prop_init();
// mbox_prop_add(TAG_GET_CLOCK_RATE, TAG_CLOCK_CORE);
// mbox_prop_call();
// MboxPropTag * prop = mbox_prop_get(TAG_GET_CLOCK_RATE);
// printf("Core Clock Rate: %d Hz\n", prop->data.buffer_32[1]);
// mbox_prop_init();
// mbox_prop_add(TAG_GET_MAX_TEMPERATURE, 0);
// mbox_prop_call();
// u32 max_temp = mbox_prop_get(TAG_GET_MAX_TEMPERATURE)->data.buffer_32[1];
// mbox_prop_init();
// mbox_prop_add(TAG_GET_TEMPERATURE, 0);
// mbox_prop_call();
// u32 cur_temp = mbox_prop_get(TAG_GET_TEMPERATURE)->data.buffer_32[1];
// printf("Core Temp: %d.%d1fC Max: %d.%dC\n", cur_temp / 1000,
//                                             cur_temp % 1000,
//                                             max_temp / 1000,
//                                             max_temp % 1000
//       );
//
// timer_sleep(1000);

