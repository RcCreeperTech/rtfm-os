#include "mailbox_prop.h"
#include "va_args.h"
#include "types.h"
#include "mailbox.h"
#include "mem.h"

static u32 tag_buffer[8192] __attribute__((aligned(16)));
static u32 tag_index = 0;

// sets up tag list header
void mbox_prop_init()
{
  tag_buffer[TB_MESSAGE_LENGTH] = 12; // bytes for header of message
  tag_buffer[TB_STATE] = TB_STATE_REQUEST;
  tag_index = 2;
  tag_buffer[tag_index] = NULL; // list must be null terminated
}

// handles adding a tag to the list
void mbox_prop_add(u32 prop_tag, ...)
{
  va_list args;

  va_start(args, prop_tag);

  tag_buffer[tag_index++] = prop_tag;

  switch(prop_tag)
  {
    case TAG_GET_FIRMWARE_VERSION:
    case TAG_GET_BOARD_MODEL:
    case TAG_GET_BOARD_REVISION:
    case TAG_GET_BOARD_MAC_ADDRESS:
    case TAG_GET_BOARD_SERIAL:
    case TAG_GET_ARM_MEMORY:
    case TAG_GET_VC_MEMORY:
    case TAG_GET_DMA_CHANNELS:
    {
      /* Provide an 8-byte buffer for the response */
      tag_buffer[tag_index++] = 8;
      tag_buffer[tag_index++] = 0; /* Request */
      tag_index += 2;
    } break;

    case TAG_GET_CLOCKS:
    case TAG_GET_COMMAND_LINE:
    {
      /* Provide a 256-byte buffer */
      tag_buffer[tag_index++] = 256;
      tag_buffer[tag_index++] = 0; /* Request */
      tag_index += 256 >> 2; // divides by 4 bc tab_buffer increments in 4 bytes
    } break;

    case TAG_ALLOCATE_BUFFER:
    case TAG_GET_MAX_CLOCK_RATE:
    case TAG_GET_MIN_CLOCK_RATE:
    case TAG_GET_CLOCK_RATE:
    case TAG_GET_TEMPERATURE:
    case TAG_GET_MAX_TEMPERATURE:
    {
      tag_buffer[tag_index++] = 8;
      tag_buffer[tag_index++] = 0; /* Request */
      tag_buffer[tag_index++] = va_arg( args, u32 );
      tag_buffer[tag_index++] = 0;
    } break;

    case TAG_SET_CLOCK_RATE:
    {
      tag_buffer[tag_index++] = 12;
      tag_buffer[tag_index++] = 0; /* Request */
      tag_buffer[tag_index++] = va_arg( args, u32 ); /* Clock ID */
      tag_buffer[tag_index++] = va_arg( args, u32 ); /* Rate (in Hz) */
      tag_buffer[tag_index++] = va_arg( args, u32 ); /* Skip turbo setting if == 1 */
    } break;

    case TAG_GET_PHYSICAL_SIZE:
    case TAG_SET_PHYSICAL_SIZE:
    case TAG_TEST_PHYSICAL_SIZE:
    case TAG_GET_VIRTUAL_SIZE:
    case TAG_SET_VIRTUAL_SIZE:
    case TAG_TEST_VIRTUAL_SIZE:
    case TAG_GET_VIRTUAL_OFFSET:
    case TAG_SET_VIRTUAL_OFFSET:
    {
      tag_buffer[tag_index++] = 8;
      tag_buffer[tag_index++] = 0; /* Request */

      if((prop_tag == TAG_SET_PHYSICAL_SIZE ) ||
         (prop_tag == TAG_SET_VIRTUAL_SIZE  ) ||
         (prop_tag == TAG_SET_VIRTUAL_OFFSET) ||
         (prop_tag == TAG_TEST_PHYSICAL_SIZE) ||
         (prop_tag == TAG_TEST_VIRTUAL_SIZE ))
      {
        tag_buffer[tag_index++] = va_arg(args, u32); /* Width */
        tag_buffer[tag_index++] = va_arg(args, u32); /* Height */
      }
      else
      {
        tag_index += 2;
      }
    } break;

    case TAG_GET_ALPHA_MODE:
    case TAG_SET_ALPHA_MODE:
    case TAG_GET_DEPTH:
    case TAG_SET_DEPTH:
    case TAG_GET_PIXEL_ORDER:
    case TAG_SET_PIXEL_ORDER:
    case TAG_GET_PITCH:
    {
      tag_buffer[tag_index++] = 4;
      tag_buffer[tag_index++] = 0; /* Request */

      if((prop_tag == TAG_SET_DEPTH)       ||
         (prop_tag == TAG_SET_PIXEL_ORDER) ||
         (prop_tag == TAG_SET_ALPHA_MODE))
      {
        /* Colour Detag_bufferh, bits-per-pixel \ Pixel Order State */
        tag_buffer[tag_index++] = va_arg(args, u32);
      }
      else
      {
        tag_index += 1;
      }
    } break;

    case TAG_GET_OVERSCAN:
    case TAG_SET_OVERSCAN:
    {
      tag_buffer[tag_index++] = 16;
      tag_buffer[tag_index++] = 0; /* Request */

      if(prop_tag == TAG_SET_OVERSCAN)
      {
        tag_buffer[tag_index++] = va_arg(args, u32); /* Top pixels */
        tag_buffer[tag_index++] = va_arg(args, u32); /* Bottom pixels */
        tag_buffer[tag_index++] = va_arg(args, u32); /* Left pixels */
        tag_buffer[tag_index++] = va_arg(args, u32); /* Right pixels */
      }
      else
      {
        tag_index += 4;
      }
    } break;

    default:
        /* Unsupported tags, just remove the tag from the list */
        tag_index--;
        break;
  }

  tag_buffer[tag_index] = NULL;
  // idx + 1 for padding; << 2 is * 4 bc val is in bytes
  tag_buffer[TB_MESSAGE_LENGTH] = (tag_index + 1) << 2;

  va_end(args);
}

u32 mbox_prop_call()
{
  mbox_write(MBOX_CH_PROP, (u32)tag_buffer);
  return mbox_read(MBOX_CH_PROP);
}

MboxPropTag * mbox_prop_get(u32 tag)
{
  static MboxPropTag prop; // this is a big oof pls fix when virtual memort is a thing
  u32 * tag_ptr = NULL;

  u32 idx = 2;

  prop.tag = tag;

  while(idx < (tag_buffer[TB_MESSAGE_LENGTH] >> 2))
  {
    if(tag_buffer[idx] == tag)
    {
      tag_ptr = &tag_buffer[idx];
      break;
    }
    idx += (tag_buffer[idx + 1] >> 2) + 3;
  }

  if (tag_ptr == NULL)
    return NULL;

  prop.bufsize = tag_ptr[TAG_OFFSET_RESPONSE] & 0xFFFF; // should never be larger than 65535 and we dont want bit 31 anyway
  memcpy(prop.data.buffer_8, &tag_ptr[TAG_OFFSET_VALUE], prop.bufsize);

  return &prop;
}
