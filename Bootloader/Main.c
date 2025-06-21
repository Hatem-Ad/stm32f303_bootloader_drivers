#include "Bootloader.h"
#include "../Drivers/GPIO/GPIO.h"
#include "../Drivers/UART/UART.h"

int Main(void) {
    //gpio init function
    GPIO_Init();
    // uart init function
    UART_Init();
    //bootloaeder init function
    Bootloader_Init();

    while (1) {
        bootloader_run();
    }

    return 0;
}
