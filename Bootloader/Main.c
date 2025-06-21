#include "Bootloader.h"

int main(void) {
    Bootloader_Init();
    
    if (Bootloader_CheckForUpdate()) {
        Bootloader_ReceiveFirmware();
    }

    Bootloader_JumpToApp();

    while (1);
}
