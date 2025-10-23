CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -O0 -g \
         -IDrivers/GPIO \
         -IDrivers/UART \
         -IDrivers/FLASH \
         -IDrivers/SysTick \
         -IDrivers/RCC \
         -Ilib/CMSIS/Core/Include \
         -Ilib/CMSIS/Device/ST/STM32F3xx/Include

LDFLAGS = -T ../linker/App.ld

SRCS = \
     App.c \
     Drivers/GPIO/GPIO.c \
     Drivers/UART/UART.c \
     Drivers/FLASH/FLASH.c \
     Drivers/SysTick/SysTick.c \
     Drivers/RCC/RCC.c \
     startup/system_stm32f3xx.c

STARTUP = ../startup/startup_stm32f303.s

OUT = App.elf
BIN = App.bin

all: $(OUT) $(BIN)
$(OUT): $(SRCS) $(STARTUP)
	$(CC) $(CFLAGS) $(SRCS) $(STARTUP) $(LDFLAGS) -o $@

$(BIN): $(OUT)
	$(OBJCOPY) -O binary $< $@
	
clean:
	rm -f $(OUT) $(BIN)