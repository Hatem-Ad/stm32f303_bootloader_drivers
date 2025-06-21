# ===========================
# Toolchain commands
# ===========================

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

# ===========================
# Compiler flags
# ===========================

CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -O0 -g \
         -Idrivers/gpio \
         -Idrivers/uart \
         -Ibootloader
LDFLAGS = -T linker/linker.ld

# ===========================
# Source files
# ===========================

SRCS = \
    bootloader/main.c \
    bootloader/bootloader.c \
    drivers/gpio/gpio.c \
    drivers/uart/uart.c \
    startup/system_stm32f3xx.c

STARTUP = startup/startup_stm32f303.s

# ===========================
# Output names
# ===========================

OUT = build/bootloader.elf
BIN = build/bootloader.bin

# ===========================
# Build rules
# ===========================

all: $(OUT) $(BIN)

build:
	mkdir -p build

$(OUT): build $(SRCS) $(STARTUP)
	$(CC) $(CFLAGS) $(SRCS) $(STARTUP) $(LDFLAGS) -o $(OUT)

$(BIN): $(OUT)
	$(OBJCOPY) -O binary $(OUT) $(BIN)

clean:
	rm -rf build
