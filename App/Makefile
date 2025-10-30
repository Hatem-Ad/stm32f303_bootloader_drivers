CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -O0 -g \
         -I../Drivers/GPIO \
         -I../Drivers/UART \
         -I../Drivers/FLASH \
         -I../Drivers/SysTick \
         -I../Drivers/RCC \
         -I../lib/CMSIS/Core/Include \
         -I../lib/CMSIS/Device/ST/STM32F3xx/Include

LDFLAGS = -T ../linker/App.ld

SRCS = \
     App.c \
     ../Drivers/GPIO/GPIO.c \
     ../Drivers/UART/UART.c \
     ../Drivers/FLASH/FLASH.c \
     ../Drivers/SysTick/SysTick.c \
     ../Drivers/RCC/RCC.c \
     ../startup/system_stm32f3xx.c

STARTUP = ../startup/startup_stm32f303.s

OUT = App.elf
BIN = App.bin

all: $(OUT) $(BIN)

$(OUT): $(SRCS) $(STARTUP)
	$(CC) $(CFLAGS) $(SRCS) $(STARTUP) $(LDFLAGS) \
	-nostartfiles -nostdlib --specs=nosys.specs -o $@

$(BIN): $(OUT)
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(OUT) $(BIN)
