#include "Bootloader.h"

int main(void) {
//init phase 
    Bootloader_Init();
    
    if (Bootloader_CheckForUpdate()) {
        Bootloader_ReceiveFirmware();
    }
//jump to the apps 
    Bootloader_JumpToApp();

    while (1);
}
