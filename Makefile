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
         -IDrivers/GPIO \
         -IDrivers/UART \
         -IBootloader \
         -Ilib/CMSIS/Core/Include \
         -Ilib/CMSIS/Device/ST/STM32F3xx/Include \
         -IDrivers/FLASH \
         -IDrivers/SysTick \
         -IDrivers/RCC 
LDFLAGS = -T linker/Bootloader.ld
LDFLAGS = -T linker/App.ld

# ===========================
# Source files
# ===========================

SRCS = \
    Bootloader/Main.c \
    Bootloader/Bootloader.c \
    Drivers/GPIO/GPIO.c \
    Drivers/UART/UART.c \
    startup/system_stm32f3xx.c \
    Drivers/FLASH/FLASH.c \
    Drivers/SysTick/SysTick.c

STARTUP = startup/startup_stm32f303.s

# ===========================
# Output names
# ===========================

OUT = build/Bootloader.elf
BIN = build/Bootloader.bin

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
