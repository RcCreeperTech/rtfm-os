#pragma once
#include "mmio/v3d_bridge.h"

# define V3D_TOP_GR_BRIDGE_MAJOR_MASK                  0xff00
# define V3D_TOP_GR_BRIDGE_MAJOR_SHIFT                 8
# define V3D_TOP_GR_BRIDGE_MINOR_MASK                  0xff
# define V3D_TOP_GR_BRIDGE_MINOR_SHIFT                 0

/* 7268 reset reg */
# define V3D_TOP_GR_BRIDGE_SW_INIT_0_V3D_CLK_108_SW_INIT (1 << 0)
/* 7278 reset reg */
# define V3D_TOP_GR_BRIDGE_SW_INIT_1_V3D_CLK_108_SW_INIT (1 << 0)
