#pragma once
#include "types.h"

#define TAG_GET_FIRMWARE_VERSION    0x00001
#define TAG_GET_BOARD_MODEL         0x10001
#define TAG_GET_BOARD_REVISION      0x10002
#define TAG_GET_BOARD_MAC_ADDRESS   0x10003
#define TAG_GET_BOARD_SERIAL        0x10004
#define TAG_GET_ARM_MEMORY          0x10005
#define TAG_GET_VC_MEMORY           0x10006
#define TAG_GET_CLOCKS              0x10007
#define TAG_GET_COMMAND_LINE        0x50001
#define TAG_GET_DMA_CHANNELS        0x60001
#define TAG_GET_POWER_STATE         0x20001
#define TAG_GET_TIMING              0x20002
#define TAG_SET_POWER_STATE         0x28001
#define TAG_GET_CLOCK_STATE         0x30001
#define TAG_SET_CLOCK_STATE         0x38001
#define TAG_GET_CLOCK_RATE          0x30002
#define TAG_SET_CLOCK_RATE          0x38002
#define TAG_GET_MAX_CLOCK_RATE      0x30004
#define TAG_GET_MIN_CLOCK_RATE      0x30007
#define TAG_GET_TURBO               0x30009
#define TAG_SET_TURBO               0x38009
#define TAG_GET_VOLTAGE             0x30003
#define TAG_SET_VOLTAGE             0x38003
#define TAG_GET_MAX_VOLTAGE         0x30005
#define TAG_GET_MIN_VOLTAGE         0x30008
#define TAG_GET_TEMPERATURE         0x30006
#define TAG_GET_MAX_TEMPERATURE     0x3000A
#define TAG_ALLOCATE_MEMORY         0x3000C
#define TAG_LOCK_MEMORY             0x3000D
#define TAG_UNLOCK_MEMORY           0x3000E
#define TAG_RELEASE_MEMORY          0x3000F
#define TAG_EXECUTE_CODE            0x30010
#define TAG_GET_DISPMANX_MEM_HANDLE 0x30014
#define TAG_GET_EDID_BLOCK          0x30020
#define TAG_ALLOCATE_BUFFER         0x40001
#define TAG_RELEASE_BUFFER          0x48001
#define TAG_BLANK_SCREEN            0x40002
#define TAG_GET_PHYSICAL_SIZE       0x40003
#define TAG_TEST_PHYSICAL_SIZE      0x44003
#define TAG_SET_PHYSICAL_SIZE       0x48003
#define TAG_GET_VIRTUAL_SIZE        0x40004
#define TAG_TEST_VIRTUAL_SIZE       0x44004
#define TAG_SET_VIRTUAL_SIZE        0x48004
#define TAG_GET_DEPTH               0x40005
#define TAG_TEST_DEPTH              0x44005
#define TAG_SET_DEPTH               0x48005
#define TAG_GET_PIXEL_ORDER         0x40006
#define TAG_TEST_PIXEL_ORDER        0x44006
#define TAG_SET_PIXEL_ORDER         0x48006
#define TAG_GET_ALPHA_MODE          0x40007
#define TAG_TEST_ALPHA_MODE         0x44007
#define TAG_SET_ALPHA_MODE          0x48007
#define TAG_GET_PITCH               0x40008
#define TAG_GET_VIRTUAL_OFFSET      0x40009
#define TAG_TEST_VIRTUAL_OFFSET     0x44009
#define TAG_SET_VIRTUAL_OFFSET      0x48009
#define TAG_GET_OVERSCAN            0x4000A
#define TAG_TEST_OVERSCAN           0x4400A
#define TAG_SET_OVERSCAN            0x4800A
#define TAG_GET_PALETTE             0x4000B
#define TAG_TEST_PALETTE            0x4400B
#define TAG_SET_PALETTE             0x4800B
#define TAG_SET_CURSOR_INFO         0x08011
#define TAG_SET_CURSOR_STATE        0x08010

#define TAG_CLOCK_RESERVED 0
#define TAG_CLOCK_EMMC     1
#define TAG_CLOCK_UART     2
#define TAG_CLOCK_ARM      3
#define TAG_CLOCK_CORE     4
#define TAG_CLOCK_V3D      5
#define TAG_CLOCK_H264     6
#define TAG_CLOCK_ISP      7
#define TAG_CLOCK_SDRAM    8
#define TAG_CLOCK_PIXEL    9
#define TAG_CLOCK_PWM      10

#define TB_MESSAGE_LENGTH 0
#define TB_STATE          1

#define TB_STATE_REQUEST  0
#define TB_STATE_RESPONSE 1

#define TB_REQUEST  0
#define TB_RESPONSE (1 << 31)

#define TAG_OFFSET_ID       0
#define TAG_OFFSET_BUFSIZE  1
#define TAG_OFFSET_RESPONSE 2 // holds len of returned val in bytes
#define TAG_OFFSET_VALUE    3
typedef struct MboxPropTag
{
  u32 tag;
  u32 bufsize; // in bytes
  union
  {
    u32 value_32;
    u8 buffer_8[256];
    u32 buffer_32[64];
  } data;
} MboxPropTag;

void          mbox_prop_init();
void          mbox_prop_add(u32 prop_tag, ...);
u32           mbox_prop_call();
MboxPropTag * mbox_prop_get(u32 tag);
