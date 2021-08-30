#pragma once
#include "types.h"
#include "mmio/base.h"
#include "mmio/irq.h"

// REG 0
#define VC_IRQ_SYSTEM_TIMER0 (1 << 0)
#define VC_IRQ_SYSTEM_TIMER1 (1 << 1)
#define VC_IRQ_SYSTEM_TIMER2 (1 << 2)
#define VC_IRQ_SYSTEM_TIMER3 (1 << 3)
#define VC_IRQ_AUX           (1 << 29)

// REG 1
#define VC_IRQ_SMI           (1 << 16) // mapped to vsync fuck this shit
#define SMI_CS 0xFE600000 // i hate you

extern void irq_vtable_init();
extern void enable_irq();
extern void disable_irq();

void enable_interrupt_controller();
