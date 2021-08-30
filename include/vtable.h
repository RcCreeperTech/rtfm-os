#pragma once

#define STACK_FRAME_SIZE 256

#define EE_EL1t_SYNC    0
#define EE_EL1t_IRQ     1
#define EE_EL1t_FIQ     2
#define EE_EL1t_ERROR   3

#define EE_EL1h_SYNC    4
#define EE_EL1h_IRQ     5
#define EE_EL1h_FIQ     6
#define EE_EL1h_ERROR   7

#define EE_EL0_64_SYNC  8
#define EE_EL0_64_IRQ   9
#define EE_EL0_64_FIQ   10
#define EE_EL0_64_ERROR 11

#define EE_EL0_32_SYNC  12
#define EE_EL0_32_IRQ   13
#define EE_EL0_32_FIQ   14
#define EE_EL0_32_ERROR 15
