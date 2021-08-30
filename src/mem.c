#include "mem.h"

void * memcpy(void * dest, void * src, u64 bytes)
{
  u8 * bsrc  =  (u8 *)src;
  u8 * bdest =  (u8 *)dest;
  for(u32 i = 0; i < bytes; i++) bdest[i] = bsrc[i];
  return dest;
}
