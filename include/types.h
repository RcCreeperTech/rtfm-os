#pragma once

#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ s8;
#endif
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ s16;
#endif
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ s32;
#endif
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ s64;
#endif
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ u8;
#endif
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ u16;
#endif
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ u32;
#endif
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ u64;
#endif

typedef volatile u8  reg8;
typedef volatile u32 reg32;

#define bool	_Bool
#if defined __STDC_VERSION__ && __STDC_VERSION__ > 201710L
#define true	((_Bool)+1u)
#define false	((_Bool)+0u)
#else
#define true	1
#define false	0
#endif

#define NULL 0
