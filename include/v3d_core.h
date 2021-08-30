#pragma once
#include "mmio/v3d_core.h"

#define WIERD_MACROS 0

/* Per-V3D-core registers */
#define V3D_IDENT0_VER_MASK                           0xff000000
#define V3D_IDENT0_VER_SHIFT                          24

/* Multiples of 1kb */
#define V3D_IDENT1_VPM_SIZE_MASK                      0xf0000000
#define V3D_IDENT1_VPM_SIZE_SHIFT                     28
#define V3D_IDENT1_NSEM_MASK                          0xff0000
#define V3D_IDENT1_NSEM_SHIFT                         16
#define V3D_IDENT1_NTMU_MASK                          0xf000
#define V3D_IDENT1_NTMU_SHIFT                         12
#define V3D_IDENT1_QUPS_MASK                          0xf00
#define V3D_IDENT1_QUPS_SHIFT                         8
#define V3D_IDENT1_NSLC_MASK                          0xf0
#define V3D_IDENT1_NSLC_SHIFT                         4
#define V3D_IDENT1_REV_MASK                           0xf
#define V3D_IDENT1_REV_SHIFT                          0

#define V3D_IDENT2_BCG_INT                            (1 << 28)

#define V3D_CTL_MISCCFG_QRMAXCNT_MASK                 0xe
#define V3D_CTL_MISCCFG_QRMAXCNT_SHIFT                1
#define V3D_MISCCFG_OVRTMUOUT                         (1 << 0)

#define V3D_L2CACTL_L2CCLR                            (1 << 2)
#define V3D_L2CACTL_L2CDIS                            (1 << 1)
#define V3D_L2CACTL_L2CENA                            (1 << 0)

#define V3D_SLCACTL_TVCCS_MASK                        0xf000000
#define V3D_SLCACTL_TVCCS_SHIFT                       24
#define V3D_SLCACTL_TDCCS_MASK                        0xf0000
#define V3D_SLCACTL_TDCCS_SHIFT                       16
#define V3D_SLCACTL_UCC_MASK                          0xf00
#define V3D_SLCACTL_UCC_SHIFT                         8
#define V3D_SLCACTL_ICC_MASK                          0xf
#define V3D_SLCACTL_ICC_SHIFT                         0

#define V3D_L2TCACTL_TMUWCF                           (1 << 8)
#define V3D_L2TCACTL_L2T_NO_WM                        (1 << 4)
/* Invalidates cache lines. */
#define V3D_L2TCACTL_FLM_FLUSH                        0
/* Removes cachelines without writing dirty lines back. */
#define V3D_L2TCACTL_FLM_CLEAR                        1
/* Writes out dirty cachelines and marks them clean, but doesn't invalidate. */
#define V3D_L2TCACTL_FLM_CLEAN                        2
#define V3D_L2TCACTL_FLM_MASK                         0x6
#define V3D_L2TCACTL_FLM_SHIFT                        1
#define V3D_L2TCACTL_L2TFLS                           (1 << 0)
#define V3D_INT_QPU_MASK                              0xfff0000
#define V3D_INT_QPU_SHIFT                             16
#define V3D_INT_CSDDONE                               (1 << 7)
#define V3D_INT_PCTR                                  (1 << 6)
#define V3D_INT_GMPV                                  (1 << 5)
#define V3D_INT_TRFB                                  (1 << 4)
#define V3D_INT_SPILLUSE                              (1 << 3)
#define V3D_INT_OUTOMEM                               (1 << 2)
#define V3D_INT_FLDONE                                (1 << 1)
#define V3D_INT_FRDONE                                (1 << 0)

#if WIERD_MACORS
  #define V3D_CLE_CTNCS(n) (V3D_CLE_CT0CS + 4 * n)
  #define V3D_CLE_CTNEA(n) (V3D_CLE_CT0EA + 4 * n)
  #define V3D_CLE_CTNCA(n) (V3D_CLE_CT0CA + 4 * n)
  #define V3D_CLE_CTNRA(n) (V3D_CLE_CT0RA + 4 * n)

  #define V3D_CLE_CTNQBA(n) (V3D_CLE_CT0QBA + 4 * n)
  #define V3D_CLE_CTNQEA(n) (V3D_CLE_CT0QEA + 4 * n)

  #define V3D_V3_PCTR_0_PCTRSX(x) (V3D_V3_PCTR_0_PCTRS0 + 4 * (x))
  #define V3D_PCTR_0_PCTRX(x) (V3D_PCTR_0_PCTR0 + 4 * (x))
#endif

#define V3D_CLE_CT0QTS_ENABLE                         (1 << 1)
/* If set without ETPROC, entirely skip tiles with no primitives. */
#define V3D_CLE_QCFG_ETFILT                           (1 << 7)
/* If set with ETFILT, just write the clear color to tiles with no
 * primitives.
 */
#define V3D_CLE_QCFG_ETPROC                           (1 << 6)
#define V3D_CLE_QCFG_ETSFLUSH                         (1 << 1)
#define V3D_CLE_QCFG_MCDIS                            (1 << 0)

#define V3D_PTB_BXCF_RWORDERDISA                      (1 << 1)
#define V3D_PTB_BXCF_CLIPDISA                         (1 << 0)

#define V3D_V3_PCTR_0_EN_ENABLE                       (1 << 31)
/* Each src reg muxes four counters each. */
#define V3D_PCTR_S0_MASK                              0x7f
#define V3D_PCTR_S0_SHIFT                             0
#define V3D_PCTR_S1_MASK                              0x7f00
#define V3D_PCTR_S1_SHIFT                             8
#define V3D_PCTR_S2_MASK                              0x7f0000
#define V3D_PCTR_S2_SHIFT                             16
#define V3D_PCTR_S3_MASK                              0x7f000000
#define V3D_PCTR_S3_SHIFT                             24
#define V3D_PCTR_CYCLE_COUNT                          32

/* Output values of the counters. */
#define V3D_GMP_STATUS_GMPRST                         (1 << 31)
#define V3D_GMP_STATUS_WR_COUNT_MASK                  0x7f000000
#define V3D_GMP_STATUS_WR_COUNT_SHIFT                 24
#define V3D_GMP_STATUS_RD_COUNT_MASK                  0x7f0000
#define V3D_GMP_STATUS_RD_COUNT_SHIFT                 16
#define V3D_GMP_STATUS_WR_ACTIVE                      (1 << 5)
#define V3D_GMP_STATUS_RD_ACTIVE                      (1 << 4)
#define V3D_GMP_STATUS_CFG_BUSY                       (1 << 3)
#define V3D_GMP_STATUS_CNTOVF                         (1 << 2)
#define V3D_GMP_STATUS_INVPROT                        (1 << 1)
#define V3D_GMP_STATUS_VIO                            (1 << 0)

#define V3D_GMP_CFG_LBURSTEN                          (1 << 3)
#define V3D_GMP_CFG_PGCRSEN                           (1 << )
#define V3D_GMP_CFG_STOP_REQ                          (1 << 1)
#define V3D_GMP_CFG_PROT_ENABLE                       (1 << 0)

#define V3D_CSD_STATUS_NUM_COMPLETED_MASK             0xff0
#define V3D_CSD_STATUS_NUM_COMPLETED_SHIFT            4
#define V3D_CSD_STATUS_NUM_ACTIVE_MASK                0xc
#define V3D_CSD_STATUS_NUM_ACTIVE_SHIFT               2
#define V3D_CSD_STATUS_HAVE_CURRENT_DISPATCH          (1 << 1)
#define V3D_CSD_STATUS_HAVE_QUEUED_DISPATCH           (1 << 0)

#define V3D_CSD_QUEUED_CFG0_NUM_WGS_X_MASK            0xffff0000
#define V3D_CSD_QUEUED_CFG0_NUM_WGS_X_SHIFT           16
#define V3D_CSD_QUEUED_CFG0_WG_X_OFFSET_MASK          0xffff
#define V3D_CSD_QUEUED_CFG0_WG_X_OFFSET_SHIFT         0

#define V3D_CSD_QUEUED_CFG1_NUM_WGS_Y_MASK            0xffff0000
#define V3D_CSD_QUEUED_CFG1_NUM_WGS_Y_SHIFT           16
#define V3D_CSD_QUEUED_CFG1_WG_Y_OFFSET_MASK          0xffff
#define V3D_CSD_QUEUED_CFG1_WG_Y_OFFSET_SHIFT         0

#define V3D_CSD_QUEUED_CFG2_NUM_WGS_Z_MASK            0xffff0000
#define V3D_CSD_QUEUED_CFG2_NUM_WGS_Z_SHIFT           16
#define V3D_CSD_QUEUED_CFG2_WG_Z_OFFSET_MASK          0xffff
#define V3D_CSD_QUEUED_CFG2_WG_Z_OFFSET_SHIFT         0

#define V3D_CSD_QUEUED_CFG3_OVERLAP_WITH_PREV         (1 << 26)
#define V3D_CSD_QUEUED_CFG3_MAX_SG_ID_MASK            0x3f00000
#define V3D_CSD_QUEUED_CFG3_MAX_SG_ID_SHIFT           20
#define V3D_CSD_QUEUED_CFG3_BATCHES_PER_SG_M1_MASK    0xff000
#define V3D_CSD_QUEUED_CFG3_BATCHES_PER_SG_M1_SHIFT   12
#define V3D_CSD_QUEUED_CFG3_WGS_PER_SG_MASK           0xf00
#define V3D_CSD_QUEUED_CFG3_WGS_PER_SG_SHIFT          8
#define V3D_CSD_QUEUED_CFG3_WG_SIZE_MASK              0xff
#define V3D_CSD_QUEUED_CFG3_WG_SIZE_SHIFT             0

#define V3D_CSD_CURRENT_ID0_WG_X_MASK                 0xffff0000
#define V3D_CSD_CURRENT_ID0_WG_X_SHIFT                16
#define V3D_CSD_CURRENT_ID0_WG_IN_SG_MASK             0xf00
#define V3D_CSD_CURRENT_ID0_WG_IN_SG_SHIFT            8
#define V3D_CSD_CURRENT_ID0_L_IDX_MASK                0xff
#define V3D_CSD_CURRENT_ID0_L_IDX_SHIFT               0

#define V3D_CSD_CURRENT_ID0_WG_Z_MASK                 0xffff0000
#define V3D_CSD_CURRENT_ID0_WG_Z_SHIFT                16
#define V3D_CSD_CURRENT_ID0_WG_Y_MASK                 0xffff
#define V3D_CSD_CURRENT_ID0_WG_Y_SHIFT                0

#define V3D_ERR_FDBGS_INTERPZ_IP_STALL                (1 << 17)
#define V3D_ERR_FDBGS_DEPTHO_FIFO_IP_STALL            (1 << 16)
#define V3D_ERR_FDBGS_XYNRM_IP_STALL                  (1 << 14)
#define V3D_ERR_FDBGS_EZREQ_FIFO_OP_VALID             (1 << 13)
#define V3D_ERR_FDBGS_QXYF_FIFO_OP_VALID              (1 << 12)
#define V3D_ERR_FDBGS_QXYF_FIFO_OP_LAST               (1 << 11)
#define V3D_ERR_FDBGS_EZTEST_ANYQVALID                (1 << 7)
#define V3D_ERR_FDBGS_EZTEST_PASS                     (1 << 6)
#define V3D_ERR_FDBGS_EZTEST_QREADY                   (1 << 5)
#define V3D_ERR_FDBGS_EZTEST_VLF_OKNOVALID            (1 << 4)
#define V3D_ERR_FDBGS_EZTEST_QSTALL                   (1 << 3)
#define V3D_ERR_FDBGS_EZTEST_IP_VLFSTALL              (1 << 2)
#define V3D_ERR_FDBGS_EZTEST_IP_PRSTALL               (1 << 1)
#define V3D_ERR_FDBGS_EZTEST_IP_QSTALL                (1 << 0)

#define V3D_ERR_L2CARE                                (1 << 15)
#define V3D_ERR_VCMBE                                 (1 << 14)
#define V3D_ERR_VCMRE                                 (1 << 13)
#define V3D_ERR_VCDI                                  (1 << 12)
#define V3D_ERR_VCDE                                  (1 << 11)
#define V3D_ERR_VDWE                                  (1 << 10)
#define V3D_ERR_VPMEAS                                (1 << 9)
#define V3D_ERR_VPMEFNA                               (1 << 8)
#define V3D_ERR_VPMEWNA                               (1 << 7)
#define V3D_ERR_VPMERNA                               (1 << 6)
#define V3D_ERR_VPMERR                                (1 << 5)
#define V3D_ERR_VPMEWR                                (1 << 4)
#define V3D_ERR_VPAERRGL                              (1 << 3)
#define V3D_ERR_VPAEBRGL                              (1 << 2)
#define V3D_ERR_VPAERGS                               (1 << 1)
#define V3D_ERR_VPAEABB                               (1 << 0)

