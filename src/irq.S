.global irq_vtable_init
irq_vtable_init:
  adr x0, vtable
  msr vbar_el1, x0
  ret

.global enable_irq
enable_irq:
  msr daifclr, #2 // unmask irq bit in system register
  ret

.global disable_irq
disable_irq:
  msr daifset, #2 // mask irq bit in system register
  ret
