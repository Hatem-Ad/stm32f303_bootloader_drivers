#include "bootloader.h"
#include "../drivers/gpio/gpio.h"
#include "../drivers/uart/uart.h"

int main(void) {
    gpio_init();
    uart_init();
    bootloader_init();

    while (1) {
        bootloader_run();
    }

    return 0;
}
