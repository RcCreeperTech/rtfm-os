#include "mailbox.h"
#include "types.h"

void mbox_write(u8 channel, u32 data)
{
  while(REGS_VC_MBOX->status & MBOX_FULL);

  REGS_VC_MBOX->write = ((0xFFFFFFF0 & data) | (0xF & channel));
}

u32 mbox_read(u8 channel)
{
  u32 value = 0xFFFFFFFF;

  while((value & 0xF) != channel)
  {
    while(REGS_VC_MBOX->status & MBOX_EMPTY);
    value = REGS_VC_MBOX->read;
  }

  return value >> 4; // shift down upper 28 bits for just the value no channel
}
