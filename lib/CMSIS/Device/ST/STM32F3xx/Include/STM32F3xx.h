#ifndef STM32F3xx_H
#define STM32F3xx_H

#include <stdint.h>

/* ==========================================================
 * CMSIS-style type qualifiers for hardware register access
 * ==========================================================
 * __I   = read-only
 * __O   = write-only
 * __IO  = read/write
 * These expand to 'volatile' to prevent compiler optimization.
 */
#define __I     volatile const /*!< Defines 'read only' permissions */
#define __O     volatile       /*!< Defines 'write only' permissions */
#define __IO    volatile       /*!< Defines 'read / write' permissions */

#define C_PERIPH_BASE            ((uint32_t) 0x40000000)
#define C_AHBPERIPH_BASE         (C_PERIPH_BASE + 0x20000)
#define C_APB1PERIPH_BASE        (C_PERIPH_BASE + 0x00000)
#define C_APB2PERIPH_BASE        (C_PERIPH_BASE + 0x10000)



//--------------------//
//        RCC         //
//--------------------//

//RCC base address
#define C_RCC_BASE               (C_AHBPERIPH_BASE + 0x1000)

//RCC register structre
typedef struct {
    __IO uint32_t CR;
    __IO uint32_t CFGR;
    __IO uint32_t CIR;
    __IO uint32_t APB2RSTR;
    __IO uint32_t APB1RSTR;
    __IO uint32_t AHBENR;
    __IO uint32_t APB2ENR;
    __IO uint32_t APB1ENR;
    __IO uint32_t BDCR;
    __IO uint32_t CSR;
    __IO uint32_t AHBRSTR;
    __IO uint32_t CFGR2;
    __IO uint32_t CFGR3;
    __IO uint32_t CR2;
} TS_RCC_TypeDef;

//Pointers to devices
#define RCC                    ((TS_RCC_TypeDef *) C_RCC_BASE)

//RCC AHBENR bits
#define C_RCC_AHBENR_GPIOAEN   (1U << 17) // Bit 17: IO port A clock enable 
#define C_RCC_AHBENR_GPIOBEN   (1U << 18) // Bit 17: IO port B clock enable 
#define C_RCC_AHBENR_GPIOCEN   (1U << 19) // Bit 17: IO port C clock enable 
#define C_RCC_AHBENR_GPIODEN   (1U << 20) // Bit 17: IO port D clock enable 
#define C_RCC_AHBENR_GPIOEEN   (1U << 21) // Bit 17: IO port E clock enable 
#define C_RCC_AHBENR_GPIOFEN   (1U << 22) // Bit 17: IO port F clock enable 

// Peripheral activition bit
#define C_RCC_APB2ENR_USART1EN   (1U << 14) // Enable USART clock (APB2 bus)

//--------------------//
//       Flash        //
//--------------------//

//Flash peripheral base address
#define C_FLASH_BASE 0x40022000UL

//Flash register structre
typedef struct {
    __IO uint32_t ACR;     // 0x00: Access control register
    __IO uint32_t KEYR;    // 0x04: Key register
    __IO uint32_t OPTKEYR; // 0x08: Option key register
    __IO uint32_t SR;      // 0x0C: Status register
    __IO uint32_t CR;      // 0x10: Control register
    __IO uint32_t AR;      // 0x14: Address register
         uint32_t RESERVED;
    __I  uint32_t OBR;     // 0x1C: Option byte register
    __I  uint32_t WRPR;    // 0x20: Write protection register
} TS_FLASH_TypeDef;

//Flash pointer
#define FLASH ((TS_FLASH_TypeDef *) C_FLASH_BASE)

// Flash key values (from RM0316 reference manual)
#define C_FLASH_KEY1 0x45670123UL
#define C_FLASH_KEY2 0xCDEF89ABUL

//FLASH_CR bits
#define C_FLASH_CR_PG       (1U << 0) // PG (Programming) bit — when set, flash enters program mode (half-word write).
#define C_FLASH_CR_PER      (1U << 1) // PER (Page Erase) bit — when set, flash enters page erase mode.
#define C_FLASH_CR_START    (1U << 6) // when set, triggers the erase/program operation (used with PER or MER).
#define C_FLASH_CR_LOCK     (1U << 7) // OCK bit — when set, the flash control register is locked to prevent accidental erase/write; must be unlocked with the key sequence.

// FLASH_SR bits
#define C_FLASH_SR_BSY      (1U << 0) // Busy flag
#define C_FLASH_SR_PGERR    (1U << 2) // Programmin error
#define C_FLASH_SR_WRPERR   (1U << 4) // Write Protectoin eorrer
#define C_FLASH_SR_EOP      (1U << 5) // End of operation flag

//--------------------//
//        GPIO        //
//--------------------//

//GPIO peripheral base address
#define GPIOA_BASE             (C_AHBPERIPH_BASE + 0x0000)
#define GPIOB_BASE             (C_AHBPERIPH_BASE + 0x0400)
#define GPIOC_BASE             (C_AHBPERIPH_BASE + 0x0800)
#define GPIOD_BASE             (C_AHBPERIPH_BASE + 0x0C00)
#define GPIOE_BASE             (C_AHBPERIPH_BASE + 0x1000)
#define GPIOF_BASE             (C_AHBPERIPH_BASE + 0x1400)

//GPIOs pointer
#define GPIOA ((TS_GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((TS_GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC ((TS_GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD ((TS_GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE ((TS_GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF ((TS_GPIO_TypeDef *) GPIOF_BASE)

//GPIO register structre
typedef struct{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;    // ODR : Output Data Register  
    volatile uint32_t BSRR;   // BSRR : Bit Set/Reset Register
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} TS_GPIO_TypeDef;





//--------------------//
//        UART        //
//--------------------//

//UASRT peripheral base address
#define C_USART1_BASE            (C_APB2PERIPH_BASE + 0x3800)

//USART register structre
typedef struct{
    volatile uint32_t CR1;     // Control register 1
    volatile uint32_t CR2;     // Control register 2
    volatile uint32_t CR3;     // Control register 3
    volatile uint32_t BRR;     // Baud rate register
    volatile uint32_t GTPR;    // Guard time and prescaler
    volatile uint32_t RTOR;    // Receiver timeout
    volatile uint32_t RQR;     // Request register
    volatile uint32_t ISR;     // Interrupt and status register
    volatile uint32_t ICR;     // Interrupt flag clear register
    volatile uint32_t RDR;     // Receive data register
    volatile uint32_t TDR;     // Transmit data register
} TS_USART_TypeDef;

//USART1 pointer
#define USART1 ((TS_USART_TypeDef *) C_USART1_BASE)

//Controle register bits (CR)
#define C_USART_CR_TE         (1U << 3)
#define C_USART_CR_RE         (1U << 2)
#define C_USART_CR_UE         (1U << 13)

//Interrupt register status bits (ISR)
#define C_USART_ISR_FE        (1U << 1) // Farming error
#define C_USART_ISR_NE        (1U << 2) // Noise error
#define C_USART_ISR_ORE       (1U << 3) // Overrun error  
#define C_USART_ISR_RXNE      (1U << 5) // Read date register not empty
#define C_USART_ISR_TC        (1U << 6) // Transmission complete
#define C_USART_ISR_TXE       (1U << 7) // Transmit data regisyter empty

#endif