# ===========================
# Toolchain commands
# ===========================

CC = arm-none-eabi-gcc       # The compiler for ARM Cortex-M
AS = arm-none-eabi-as        # Assembler (not used here, but could be)
LD = arm-none-eabi-ld        # Linker (optional if not using gcc to link)
OBJCOPY = arm-none-eabi-objcopy  # Converts ELF to binary

# ===========================
# Compiler flags
# ===========================

CFLAGS = -mcpu=cortex-m4     # Target CPU: Cortex-M4 core
         -mthumb             # Use Thumb instruction set
         -Wall               # Enable all compiler warnings
         -O0                 # No optimization (good for debug)
         -g                  # Include debug information

LDFLAGS = -T linker/linker.ld  # Linker script to control memory layout

# ===========================
# Project source files
# ===========================

SRCS = \
    bootloader/main.c \        # Main bootloader code
    bootloader/bootloader.c \  # Bootloader logic
    drivers/gpio/gpio.c \      # GPIO driver
    drivers/uart/uart.c \      # UART driver
    startup/system_stm32f3xx.c # System init file

STARTUP = startup/startup_stm32f303.s  # Startup assembly file with vector table

# ===========================
# Output names
# ===========================

OUT = build/bootloader.elf     # The final ELF executable (for debug/load)
BIN = build/bootloader.bin     # The binary file for flashing

# ===========================
# Build rules
# ===========================

all: $(OUT) $(BIN)             # Default rule: build ELF and BIN

build:
	mkdir -p build             # Ensure build directory exists

$(OUT): build $(SRCS) $(STARTUP)
	$(CC) $(CFLAGS) $(SRCS) $(STARTUP) $(LDFLAGS) -o $(OUT)  
        # Compile and link everything into an ELF

$(BIN): $(OUT)
	$(OBJCOPY) -O binary $(OUT) $(BIN)  
        # Convert ELF to binary format for flashing

clean:
	rm -rf build               # Remove build directory and files
