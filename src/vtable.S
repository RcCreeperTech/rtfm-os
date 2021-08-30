#include "vtable.h"

.macro handle_invalid_exception entry
  save_execution_context
  mov x0, #\entry
  mrs x1, esr_el1
  mrs x2, elr_el1
  bl show_exception_error
  b err_hang
.endm

.macro ventry label
  .align 7
  b \label
.endm

.macro save_execution_context
  sub sp,  sp,  #STACK_FRAME_SIZE
  stp x0,  x1,  [sp, #16 * 0]
  stp x2,  x3,  [sp, #16 * 1]
  stp x4,  x5,  [sp, #16 * 2]
  stp x6,  x7,  [sp, #16 * 3]
  stp x8,  x9,  [sp, #16 * 4]
  stp x10, x11, [sp, #16 * 5]
  stp x12, x13, [sp, #16 * 6]
  stp x14, x15, [sp, #16 * 7]
  stp x16, x17, [sp, #16 * 8]
  stp x18, x19, [sp, #16 * 9]
  stp x20, x21, [sp, #16 * 10]
  stp x22, x23, [sp, #16 * 11]
  stp x24, x25, [sp, #16 * 12]
  stp x26, x27, [sp, #16 * 13]
  stp x28, x29, [sp, #16 * 14]
  str x30,      [sp, #16 * 15]
.endm

.macro load_execution_context
  ldp x0,  x1,  [sp, #16 * 0]
  ldp x2,  x3,  [sp, #16 * 1]
  ldp x4,  x5,  [sp, #16 * 2]
  ldp x6,  x7,  [sp, #16 * 3]
  ldp x8,  x9,  [sp, #16 * 4]
  ldp x10, x11, [sp, #16 * 5]
  ldp x12, x13, [sp, #16 * 6]
  ldp x14, x15, [sp, #16 * 7]
  ldp x16, x17, [sp, #16 * 8]
  ldp x18, x19, [sp, #16 * 9]
  ldp x20, x21, [sp, #16 * 10]
  ldp x22, x23, [sp, #16 * 11]
  ldp x24, x25, [sp, #16 * 12]
  ldp x26, x27, [sp, #16 * 13]
  ldp x28, x29, [sp, #16 * 14]
  ldr x30,      [sp, #16 * 15]
  add sp,  sp,  #STACK_FRAME_SIZE
  eret
.endm

.align 11
.global vtable
vtable:
  ventry ee_el1t_sync
  ventry ee_el1t_irq
  ventry ee_el1t_fiq
  ventry ee_el1t_error

  ventry ee_el1h_sync
  ventry el1h_irq
  ventry ee_el1h_fiq
  ventry ee_el1h_error

  ventry ee_el0_64_sync
  ventry ee_el0_64_irq
  ventry ee_el0_64_fiq
  ventry ee_el0_64_error

  ventry ee_el0_32_sync
  ventry ee_el0_32_irq
  ventry ee_el0_32_fiq
  ventry ee_el0_32_error



ee_el1t_sync:    handle_invalid_exception EE_EL1t_SYNC
ee_el1t_irq:     handle_invalid_exception EE_EL1t_IRQ
ee_el1t_fiq:     handle_invalid_exception EE_EL1t_FIQ
ee_el1t_error:   handle_invalid_exception EE_EL1t_ERROR
ee_el1h_sync:    handle_invalid_exception EE_EL1h_SYNC
// el1h_irq
ee_el1h_fiq:     handle_invalid_exception EE_EL1h_FIQ
ee_el1h_error:   handle_invalid_exception EE_EL1h_ERROR
ee_el0_64_sync:  handle_invalid_exception EE_EL0_64_SYNC
ee_el0_64_irq:   handle_invalid_exception EE_EL0_64_IRQ
ee_el0_64_fiq:   handle_invalid_exception EE_EL0_64_FIQ
ee_el0_64_error: handle_invalid_exception EE_EL0_64_ERROR
ee_el0_32_sync:  handle_invalid_exception EE_EL0_32_SYNC
ee_el0_32_irq:   handle_invalid_exception EE_EL0_32_IRQ
ee_el0_32_fiq:   handle_invalid_exception EE_EL0_32_FIQ
ee_el0_32_error: handle_invalid_exception EE_EL0_32_ERROR

el1h_irq:
  save_execution_context
  bl handle_el1h_irq
  load_execution_context

.global err_hang
err_hang: b err_hang
