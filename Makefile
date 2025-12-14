# ============================================================
# Bootloader Makefile for STM32F303 (Cortex-M4)
# Baseline v1.0
# ============================================================

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# ------------------------------------------------------------
# Build directories and output files
# ------------------------------------------------------------
BUILD_DIR = build
OUT = $(BUILD_DIR)/Bootloader.elf
BIN = $(BUILD_DIR)/Bootloader.bin

# ------------------------------------------------------------
# Compiler and Linker flags
# ------------------------------------------------------------
CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -O0 -g \
         -IDrivers/GPIO \
         -IDrivers/UART \
         -IDrivers/FLASH \
         -IDrivers/SysTick \
         -IDrivers/RCC \
         -IBootloader \
         -Ilib/CMSIS/Core/Include \
         -Ilib/CMSIS/Device/ST/STM32F3xx/Include

LDFLAGS = -T linker/Bootloader.ld

# ------------------------------------------------------------
# Source files
# ------------------------------------------------------------
SRCS = \
     Bootloader/Main.c \
     Bootloader/Bootloader.c \
     Bootloader/DebugVars.c \
     Drivers/GPIO/GPIO.c \
     Drivers/UART/UART.c \
     Drivers/FLASH/FLASH.c \
     Drivers/SysTick/SysTick.c \
     Drivers/RCC/RCC.c \
     startup/system_stm32f3xx.c

STARTUP = startup/startup_stm32f303.s

# ------------------------------------------------------------
# Build rules
# ------------------------------------------------------------
all: $(OUT) $(BIN)

$(OUT): $(SRCS) $(STARTUP)
	@echo "=== Building Bootloader ==="
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRCS) $(STARTUP) $(LDFLAGS) \
	-nostartfiles -nostdlib --specs=nosys.specs -o $(OUT)
	@echo "=== Bootloader.elf created ==="

$(BIN): $(OUT)
	$(OBJCOPY) -O binary $(OUT) $(BIN)
	@echo "=== Bootloader.bin created ==="

# ------------------------------------------------------------
# Cleaning
# ------------------------------------------------------------
clean:
	rm -rf $(BUILD_DIR)
	@echo "=== Clean done ==="

# ------------------------------------------------------------
# Flash (optional target for ST-Link)
# ------------------------------------------------------------
flash: $(BIN)
	st-flash write $(BIN) 0x08000000
	@echo "=== Bootloader flashed to MCU ==="
