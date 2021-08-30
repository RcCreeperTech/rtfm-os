#pragma once
#include "types.h"

#define ATAG_CORE      0x54410001
#define ATAG_NONE      0x00000000
#define ATAG_MEM       0x54410002
#define ATAG_VIDEOTEXT 0x54410003
#define ATAG_RAMDISK   0x54410004
#define ATAG_INITRD2   0x54420005
#define ATAG_SERIAL    0x54410006
#define ATAG_REVISION  0x54410007
#define ATAG_VIDEOLFB  0x54410008
#define ATAG_CMDLINE   0x54410009

typedef struct AtagCore 
{
  u32 flags;
  u32 pagesize;
  u32 rootdev;
} AtagCore;

typedef struct AtagMem
{
  u32     size;
  u32     start;
} AtagMem;

typedef struct AtagVideoText
{
  u8  x;
  u8  y;
  u16 video_page;
  u8  video_mode;
  u8  video_cols;
  u16 video_ega_bx;
  u8  video_lines;
  u8  video_isvga;
  u16 video_points;
} AtagVideoText;

typedef struct AtagRamdisk
{
  u32 flags;
  u32 size;
  u32 start;
} AtagRamdisk;

typedef struct AtagInitrd2
{
  u32 start;
  u32 size;
} AtagInitrd2;

typedef struct AtagSerialNum
{
  u32 low;
  u32 high;
} AtagSerialNum;

typedef struct AtagRevision
{
  u32 rev;
} AtagRevision;

typedef struct AtagVideolfb
{
  u16             lfb_width;
  u16             lfb_height;
  u16             lfb_depth;
  u16             lfb_linelength;
  u32             lfb_base;
  u32             lfb_size;
  u8              red_size;
  u8              red_pos;
  u8              green_size;
  u8              green_pos;
  u8              blue_size;
  u8              blue_pos;
  u8              rsvd_size;
  u8              rsvd_pos;
} AtagVideolfb;

typedef struct AtagCmdline
{
  char    cmdline[1];
} AtagCmdline;

typedef struct AtagHeader 
{
  u32 size; /* length of tag in words including this header */
  u32 tag;  /* tag type */
} AtagHeader;

typedef struct Atag
{
  AtagHeader header;
  union
  {
    AtagCore      core;
    AtagMem       mem;
    AtagVideoText videotext;
    AtagRamdisk   ramdisk;
    AtagInitrd2   initrd2;
    AtagSerialNum serialnum;
    AtagRevision  revision;
    AtagVideolfb  videolfb;
    AtagCmdline   cmdline;
  };
} Atag;

#define TAG_NEXT(tag) (Atag *)(t + ((Atag *)t)->header.size)
#define TAG_SIZE(type) (sizeof(AtagHeader) + sizeof(type) >> 2)
