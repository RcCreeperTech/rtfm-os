#include "framebuffer.h"
#include "mailbox_prop.h"

static FramebufferData framebuffer = { 0 };

void framebuffer_init()
{
  MboxPropTag * prop = NULL;

  framebuffer.width  = 1920;
  framebuffer.height = 1080;
  framebuffer.bpp    = 32;

  // setup double buffer pointing at buffer 0
  mbox_prop_init();
    mbox_prop_add(TAG_ALLOCATE_BUFFER);
    mbox_prop_add(TAG_SET_PHYSICAL_SIZE, framebuffer.width, framebuffer.height);
    mbox_prop_add(TAG_SET_VIRTUAL_SIZE,  framebuffer.width, framebuffer.height * 2); // Allocate space for double buffer
    mbox_prop_add(TAG_SET_DEPTH, 32); // ARGB
  mbox_prop_call();

  if((prop = mbox_prop_get(TAG_ALLOCATE_BUFFER)))
  {
    framebuffer.buffers[0] = (volatile void *)(prop->data.buffer_32[0] & 0x3FFFFFFF); // convert back to arm address space
    framebuffer.buffers[1] = framebuffer.buffers[0] + (framebuffer.width * framebuffer.height * framebuffer.bpp);
  }
  framebuffer.active_buffer = 1;
}

void framebuffer_swap()
{
  if(framebuffer.active_buffer == 1)
  {
    mbox_prop_init();
      mbox_prop_add(TAG_SET_VIRTUAL_OFFSET,  0, 0);
    mbox_prop_call();
    framebuffer.active_buffer = 0;
  }
  else
  {
    mbox_prop_init();
      mbox_prop_add(TAG_SET_VIRTUAL_OFFSET,  0, framebuffer.height);
    mbox_prop_call();
    framebuffer.active_buffer = 1;
  }
}

volatile void * framebuffer_get_inactive_buffer()
{
  volatile void * buf = NULL;
  if(framebuffer.active_buffer == 1)
  {
     buf = framebuffer.buffers[0];
  }
  else
  {
     buf = framebuffer.buffers[1];
  }
  return buf;
}

void framebuffer_clear(u32 buf)
{
  reg32 * write_head = (reg32 *)framebuffer_get_inactive_buffer();
  for(u32 i = 0; i < framebuffer.width * framebuffer.height; i++)
    write_head[i] = 0;
}

void framebuffer_put_pixel(u32 x, u32 y, u32 pixel)
{
  reg32 * write_head = (reg32 *)framebuffer_get_inactive_buffer();
  u32 cx = (x < 0) ? 0 : (x > framebuffer.width) ? framebuffer.width : x;
  u32 cy = (y < 0) ? 0 : (y > framebuffer.height) ? framebuffer.height : y;
  write_head[cx + (cy * framebuffer.width)] = pixel;
}
