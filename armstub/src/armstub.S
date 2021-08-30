.global _start
mov x3, #0
_start:
  ldr x0, dtb_ptr32
  mov x1, #0
  mov x2, #0
  mov x3, #0
  ldr w4, kernel_entry32
  br x4

.ltorg

.org 0xf0
.global stub_magic
stub_magic:
  .word 0x5afe570b

.org 0xf4
.global stub_version
stub_version:
  .word 0

.org 0xf8
.globl dtb_ptr32
dtb_ptr32:
	.word 0x0

.org 0xfc
.global kernel_entry32
kernel_entry32:
  .word 0x0
