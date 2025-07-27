#ifndef STM32F3xx_H
#define STM32F3xx_H

#include <stdint.h> // required for uint32_t








//--------------------//
//       Flash        //
//--------------------//

//Flash register structre
typedef struct {
    volatile uint32_t ACR;     // 0x00: Access control register
    volatile uint32_t KEYR;    // 0x04: Key register
    volatile uint32_t OPTKEYR; // 0x08: Option key register
    volatile uint32_t SR;      // 0x0C: Status register
    volatile uint32_t CR;      // 0x10: Control register
    volatile uint32_t AR;      // 0x14: Address register
    uint32_t RESERVED;
    volatile uint32_t OBR;     // 0x1C: Option byte register
    volatile uint32_t WRPR;    // 0x20: Write protection register
} FLASH_TypeDef;

//Flash peripheral base address
#define FLASH_BASE 0x40022000UL

//Flash pointer
#define FLASH ((FLASH_TypeDef *) FLASH_BASE)

//FLASH_CR bits
#define FLASH_CR_LOCK  (1U << 7)
#define FLASH_CR_PER   (1U << 1)
#define FLASH_CR_PG    (1U << 0)
#define FLASH_CR_START (1U << 6)

// FLASH_SR bits
#define FLASH_SR_BSY   (1U << 0)

//Flash keys
#define FLASH_KEY1 0x45670123UL
#define FLASH_KEY2 0xCDEF89ABUL

//--------------------//
//        GPIO        //
//--------------------//








//--------------------//
//        UART        //
//--------------------//





#endif