#include "bootloader.h"
#include "../drivers/gpio/gpio.h"
#include "../drivers/uart/uart.h"

int main(void) {
    //gpio init function
    gpio_init();
    // uart init function
    uart_init();
    //bootloaeder init function
    bootloader_init();

    while (1) {
        bootloader_run();
    }

    return 0;
}
