#pragma once
#include "mmio/mailbox.h"

#define MBOX_CH_POWER 0
#define MBOX_CH_FB    1
#define MBOX_CH_VUART 2
#define MBOX_CH_VCHIQ 3
#define MBOX_CH_LEDS  4
#define MBOX_CH_BTNS  5
#define MBOX_CH_TOUCH 6
#define MBOX_CH_COUNT 7
#define MBOX_CH_PROP  8

#define MBOX_EMPTY    0x40000000
#define MBOX_FULL     0x80000000
#define MBOX_LEVEL    0x400000FF


void mbox_write(u8 channel, u32 data);
u32  mbox_read(u8 channel);
