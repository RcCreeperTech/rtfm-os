#pragma once
#include "types.h"

typedef struct FramebufferData
{
  u32 width;
  u32 height;
  u32 v_width;
  u32 v_height;
  u32 bpp;
  u32 active_buffer; // the buffer currently being projected to the screen
  volatile void * buffers[2];
} FramebufferData;

void framebuffer_init();
void framebuffer_swap();
void framebuffer_clear();
void framebuffer_put_pixel(u32 x, u32 y, u32 pixel);
