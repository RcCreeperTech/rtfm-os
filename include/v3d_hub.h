#pragma once
#include "mmio/v3d_hub.h"

/* Stops current job, empties input fifo. */
#define V3D_TFU_CS_TFURST                             (1 << 31)
#define V3D_TFU_CS_CVTCT_MASK                         0xFF0000
#define V3D_TFU_CS_CVTCT_SHIFT                        16
#define V3D_TFU_CS_NFREE_MASK                         0x3F00
#define V3D_TFU_CS_NFREE_SHIFT                        8
#define V3D_TFU_CS_BUSY                               (1 << 0)
/* Interrupt when FINTTHR input slots are free (0 = disabled) */
#define V3D_TFU_SU_FINTTHR_MASK                       0x3F00
#define V3D_TFU_SU_FINTTHR_SHIFT                      8
/* Skips resetting the CRC at the start of CRC generation. */
#define V3D_TFU_SU_CRCCHAIN                           (1 << 4)
/* skips writes, computes CRC of the image.  miplevels must be 0. */
#define V3D_TFU_SU_CRC                                (1 << 3)
#define V3D_TFU_SU_THROTTLE_MASK                      0x2
#define V3D_TFU_SU_THROTTLE_SHIFT                     0
/* Interrupt when the conversion is complete. */
#define V3D_TFU_ICFG_IOC                              (1 << 0)
/* Use these regs instead of the defaults. */
#define V3D_TFU_COEF0_USECOEF                         (1 << 31)

/* Per-MMU registers. */
#define V3D_MMUC_CONTROL_CLEAR                        (1 << 3)
#define V3D_MMUC_CONTROL_FLUSHING                     (1 << 2)
#define V3D_MMUC_CONTROL_FLUSH                        (1 << 1)
#define V3D_MMUC_CONTROL_ENABLE                       (1 << 0)

#define V3D_MMU_CTL_CAP_EXCEEDED                      (1 << 27)
#define V3D_MMU_CTL_CAP_EXCEEDED_ABORT                (1 << 26)
#define V3D_MMU_CTL_CAP_EXCEEDED_INT                  (1 << 25)
#define V3D_MMU_CTL_CAP_EXCEEDED_EXCEPTION            (1 << 24)
#define V3D_MMU_CTL_PT_INVALID                        (1 << 20)
#define V3D_MMU_CTL_PT_INVALID_ABORT                  (1 << 19)
#define V3D_MMU_CTL_PT_INVALID_INT                    (1 << 18)
#define V3D_MMU_CTL_PT_INVALID_EXCEPTION              (1 << 17)
#define V3D_MMU_CTL_PT_INVALID_ENABLE                 (1 << 16)
#define V3D_MMU_CTL_WRITE_VIOLATION                   (1 << 12)
#define V3D_MMU_CTL_WRITE_VIOLATION_ABORT             (1 << 11)
#define V3D_MMU_CTL_WRITE_VIOLATION_INT               (1 << 10)
#define V3D_MMU_CTL_WRITE_VIOLATION_EXCEPTION         (1 << 9)
#define V3D_MMU_CTL_TLB_CLEARING                      (1 << 7)
#define V3D_MMU_CTL_TLB_STATS_CLEAR                   (1 << 3)
#define V3D_MMU_CTL_TLB_CLEAR                         (1 << 2)
#define V3D_MMU_CTL_TLB_STATS_ENABLE                  (1 << 1)
#define V3D_MMU_CTL_ENABLE                            (1 << 0)

#define V3D_MMU_ADDR_CAP_ENABLE                       (1 << 31)
#define V3D_MMU_ADDR_CAP_MPAGE_MASK                   0x0fff
#define V3D_MMU_ADDR_CAP_MPAGE_SHIFT                  0

#define V3D_MMU_SHOOT_DOWN_SHOOTING                   (1 << 29)
#define V3D_MMU_SHOOT_DOWN_SHOOT                      (1 << 28)
#define V3D_MMU_SHOOT_DOWN_PAGE_MASK                  0xfffffff
#define V3D_MMU_SHOOT_DOWN_PAGE_SHIFT                 0

#define V3D_MMU_ILLEGAL_ADDR_ENABLE                   (1 << 31)

#define V3D_MMU_PA_WIDTH_MASK                         0xf00
#define V3D_MMU_PA_WIDTH_SHIFT                        8
#define V3D_MMU_VA_WIDTH_MASK                         0xf0
#define V3D_MMU_VA_WIDTH_SHIFT                        4
#define V3D_MMU_VERSION_MASK                          0xf
#define V3D_MMU_VERSION_SHIFT                         0

#define V3D_HUB_AXICFG_MAX_LEN_MASK                   0x0f
#define V3D_HUB_AXICFG_MAX_LEN_SHIFT                  0

#define V3D_HUB_IDENT1_WITH_MSO                       (1 << 19)
#define V3D_HUB_IDENT1_WITH_TSY                       (1 << 18)
#define V3D_HUB_IDENT1_WITH_TFU                       (1 << 17)
#define V3D_HUB_IDENT1_WITH_L3C                       (1 << 16)
#define V3D_HUB_IDENT1_TVER_SHIFT                     0
#define V3D_HUB_IDENT1_REV_SHIFT                      4
#define V3D_HUB_IDENT1_NCORES_SHIFT                   8
#define V3D_HUB_IDENT1_NHOSTS_SHIFT                   12
#define V3D_HUB_IDENT1_TVER_MASK                      0x0f
#define V3D_HUB_IDENT1_REV_MASK                       0xf0
#define V3D_HUB_IDENT1_NCORES_MASK                    0x0f00
#define V3D_HUB_IDENT1_NHOSTS_MASK                    0xf000

#define V3D_HUB_IDENT2_WITH_MMU                       (1 << 8)
#define V3D_HUB_IDENT2_L3C_NKB_MASK                   0xff
#define V3D_HUB_IDENT2_L3C_NKB_SHIFT                  0

#define V3D_HUB_IDENT3_IPREV_SHIFT                    8
#define V3D_HUB_IDENT3_IPIDX_SHIFT                    0
#define V3D_HUB_IDENT3_IPIDX_MASK                     0x00ff
#define V3D_HUB_IDENT3_IPREV_MASK                     0xff00

#define V3D_HUB_INT_MMU_WRV                           (1 << 5)
#define V3D_HUB_INT_MMU_PTI                           (1 << 4)
#define V3D_HUB_INT_MMU_CAP                           (1 << 3)
#define V3D_HUB_INT_MSO                               (1 << 2)
#define V3D_HUB_INT_TFUC                              (1 << 1)
#define V3D_HUB_INT_TFUF                              (1 << 0)
