#include "Bootloader.h"

__attribute__((section(".debugvars")))
volatile uint32_t maindbg = 0;

int main(void) {

    maindbg = 0x77777777;   // DEBUG
//Execute main program logic
    Bootloader_run();
// loop while current is on
    while (1);
}
