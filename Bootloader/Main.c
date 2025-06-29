#include "Bootloader.h"

int main(void) {
//init phase 
    Bootloader_Init();
    
//Check the bootloader update
    if (Bootloader_CheckForUpdate()) {
        Bootloader_ReceiveFirmware();
    }
//jump to the apps 
    Bootloader_JumpToApp();

    while (1);
}
