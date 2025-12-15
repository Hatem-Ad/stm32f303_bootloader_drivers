#include <stdint.h>
#include "Bootloader.h"

extern volatile uint32_t maindbg;

int main(void)
{
    maindbg = 0x11111111;   // TRACE main start

    Bootloader_run();

    maindbg = 0x22222222;   // TRACE after call (jamais atteint normalement)

    while (1);
}
