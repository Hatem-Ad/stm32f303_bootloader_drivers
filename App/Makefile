CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -O0 -g\ 
		 -IDrivers/GPIO \
		 -IDrivers/UART \
		 -Ilib/CMSIS/Core/Include \
		 -Ilib/CMSIS/Device/ST/STM32F3xx/Include

LDFLAGS = -T linker/App.ld

SRC = App.c \
      ../Drivers/GPIO/GPIO.c \
      ../Drivers/UART/UART.c \
      ../startup/startup_stm32f303.s \
      ../startup/system_stm32f3xx.c

all:
	arm-none-eabi-gcc $(CFLAGS) $(SRC) $(LDFLAGS) -o App.elf