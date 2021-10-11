#pragma once
#include "types.h"
#include "mmio/base.h"

typedef struct TextureFormatUnit
{
  reg32 chip_select; // temp name
  reg32 su;
  reg32 icfg;
  reg32 input_image_address;
  reg32 input_chroma_address;
  reg32 input_image_stride;
  reg32 input_image_uplane_address;
  reg32 output_image_address;
  reg32 output_image_size;
  reg32 yuv_coefficient[4];
  reg32 crc;
} TextureFormatUnit;

typedef struct MMU
{
  reg32 c_control; // 0x1000
  reg32 res_0[127]; // 0x1004 - 0x11FC
  reg32 ctl; // 0x1200
  reg32 pt_pa_base;
  reg32 hit;
  reg32 misses;
  reg32 stalls;
  reg32 address_cap;
  reg32 shoot_down;
  reg32 bypass_start;
  reg32 bypass_end;
  /* AXI ID of the access that faulted */
  reg32 vio_id;
  /* Address for illegal PTEs to return */
  reg32 illegal_address;
  /* Address that faulted */
  reg32 vio_address;
  reg32 debug_info;
} MMU;

/* Hub registers for shared hardware between V3D cores. */
typedef struct HubRegs
{
  reg32 axi_cfg; // 0x00
  reg32 uif_cfg; // 0x04
  reg32 ident[4]; // 0x08 - 0x14

  reg32 res_0[14]; 
  reg32 interrupt_sts; // 0x50
  reg32 interrupt_set; // 0x54
  reg32 interrupt_clear; // 0x58
  reg32 interrupt_mask_sts; // 0x5c
  reg32 interrupt_mask_set; // 0x60
  reg32 interrupt_mask_clear; // 0x64

  reg32 res_1[230]; // 0x68 - 0x3fc
  TextureFormatUnit tfu; // 0x400
  reg32 res_2[767]; // 0x404 - 0x0FFC
  MMU mmu; // 0x1000
} HubRegs;

#define HUB_OFFSET    0x0000
#define REGS_V3D_HUB ((HubRegs *)(V3D_BASE + HUB_OFFSET))
