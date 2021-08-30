# Binaries
CC=aarch64-linux-gnu-gcc-8
LD=aarch64-linux-gnu-ld
OBJ=aarch64-linux-gnu-objcopy

CFLAGS=-Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -Iexternal -Iinclude # -mgeneral-regs-only
CFALGS+=-DADVLOGS

SRC=src
BUILD=build
EXTERNAL=external
SRCS=$(wildcard $(SRC)/*.c)
SRCS+=$(wildcard $(EXTERNAL)/*.c)
SRCS+=$(wildcard $(SRC)/*.S)
OBJS=$(patsubst $(SRC)%,$(BUILD)%,$(filter %.o,$(SRCS:.S=.asm.o) $(SRCS:.c=.o)))
IMG=kernel8.img

.PHONY: all clean log
all: clean $(IMG)

# Compile all translation units to .o files
$(BUILD)/%.o: $(EXTERNAL)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD)/%.asm.o: $(SRC)/%.S
	$(CC) $(CFLAGS) -c $< -o $@

log:
	-@echo $(SRCS)
	-@echo $(OBJS)

$(IMG): $(OBJS)
	$(LD) -nostdlib -nostartfiles $(OBJS) -T link.ld -o $(BUILD)/$(IMG:.img=.elf)
	$(OBJ) -O binary $(BUILD)/$(IMG:.img=.elf) $@

clean:
	rm -rf build/*
	rm -f kernel8.img
