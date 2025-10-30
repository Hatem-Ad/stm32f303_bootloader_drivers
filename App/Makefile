# ==========================================================
#  Makefile for STM32F303 Application
#  Baseline v1.0 — Clean, Minimal, Bare-Metal Build
# ==========================================================

# ----------------------
#  Toolchain
# ----------------------
CC       = arm-none-eabi-gcc
OBJCOPY  = arm-none-eabi-objcopy

# ----------------------
#  Paths & Includes
# ----------------------
CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -O0 -g \
         -I../Drivers/GPIO \
         -I../Drivers/UART \
         -I../Drivers/FLASH \
         -I../Drivers/SysTick \
         -I../Drivers/RCC \
         -I../lib/CMSIS/Core/Include \
         -I../lib/CMSIS/Device/ST/STM32F3xx/Include

# Add these flags for cleaner memory usage
CFLAGS += -ffunction-sections -fdata-sections

# ----------------------
#  Linker script
# ----------------------
LDFLAGS = -T ../linker/App.ld \
          -Wl,--gc-sections \
          -nostartfiles -nostdlib --specs=nosys.specs

# ----------------------
#  Source files
# ----------------------
SRCS = \
     App.c \
     ../Drivers/GPIO/GPIO.c \
     ../Drivers/UART/UART.c \
     ../Drivers/FLASH/FLASH.c \
     ../Drivers/SysTick/SysTick.c \
     ../Drivers/RCC/RCC.c \
     ../startup/system_stm32f3xx.c

STARTUP = ../startup/startup_stm32f303.s

# ----------------------
#  Output files
# ----------------------
OUT = App.elf
BIN = App.bin

# ----------------------
#  Build rules
# ----------------------
all: $(OUT) $(BIN)

$(OUT): $(SRCS) $(STARTUP)
	@echo "=== Building Application ==="
	$(CC) $(CFLAGS) $(SRCS) $(STARTUP) $(LDFLAGS) -o $@
	@echo "=== Build completed ==="

$(BIN): $(OUT)
	@echo "=== Creating binary ==="
	$(OBJCOPY) -O binary $< $@
	@echo "=== Binary ready: $(BIN) ==="

clean:
	rm -f $(OUT) $(BIN)
	@echo "=== Clean done ==="
