#ifndef STM32F3xx_H
#define STM32F3xx_H

#include <stdint.h> // required for uint32_t etc ...


#define PERIPH_BASE            ((uint32_t) 0x40000000)
#define AHBPERIPH_BASE         (PERIPH_BASE + 0x20000)
#define APB1PERIPH_BASE        (PERIPH_BASE + 0x00000)
#define APB2PERIPH_BASE        (PERIPH_BASE + 0x10000)

#define RCC_BASE               (AHBPERIPH_BASE + 0x1000)

//Pointers to devices
#define RCC                    ((RCC_TypeDef *) RCC_BASE)

//RCC register structre
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t AHBRSTR;
    volatile uint32_t CFGR2;
    volatile uint32_t CFGR3;
    volatile uint32_t CR2;
} RCC_TypeDef;





//--------------------//
//       Flash        //
//--------------------//

//Flash peripheral base address
#define FLASH_BASE 0x40022000UL

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

//GPIO peripheral base address
#define GPIOA_BASE             (AHBPERIPH_BASE + 0x0000)

//GPIO register structre
typedef struct{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;








//--------------------//
//        UART        //
//--------------------//

//UASRT peripheral base address
#define USART1_BASE            (APB2PERIPH_BASE + 0x3800)

//USART register structre
typedef struct{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_TypeDef;


#endif