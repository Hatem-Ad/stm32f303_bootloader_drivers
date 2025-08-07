/*
* Simple Flash Driver Test for STM32F303
* Tests basic flash erase/write/verify operations
*/

#include "Flash.h"
#include "UART.h"
#include "STM32F3xx.h"

#define TEST_ADDRESS 0x08004000 // First page after bootloader