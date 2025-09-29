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

/* Base address of Reset and Clock Control (RCC) registers */
#define C_RCC_BASE               (C_AHBPERIPH_BASE + 0x1000)

//RCC register layout
typedef struct {
    __IO uint32_t CR;        // Clock control register
    __IO uint32_t CFGR;      // Clock configuration register
    __IO uint32_t CIR;       // Clock interrupt register
    __IO uint32_t APB2RSTR;  // APB2 peripheral reset register 
    __IO uint32_t APB1RSTR;  // APB1 peripheral reset register
    __IO uint32_t AHBENR;    // AHB peripheral clock enable register 
    __IO uint32_t APB2ENR;   // APB2 peripheral clock enable register 
    __IO uint32_t APB1ENR;   // APB1 peripheral clock enable register
    __IO uint32_t BDCR;      // Backup domain control register
    __IO uint32_t CSR;       // Control/status register
    __IO uint32_t AHBRSTR;   // AHB peripheral reset register 
    __IO uint32_t CFGR2;     // Clock configuration register 2
    __IO uint32_t CFGR3;     // Clock configuration register 3
    __IO uint32_t CR2;       // Clock control register 2 
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
         uint32_t RESERVED;// 0x18 
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
#define GPIOA_BASE  (C_AHBPERIPH_BASE + 0x0000)
#define GPIOB_BASE  (C_AHBPERIPH_BASE + 0x0400)
#define GPIOC_BASE  (C_AHBPERIPH_BASE + 0x0800)
#define GPIOD_BASE  (C_AHBPERIPH_BASE + 0x0C00)
#define GPIOE_BASE  (C_AHBPERIPH_BASE + 0x1000)
#define GPIOF_BASE  (C_AHBPERIPH_BASE + 0x1400)

//GPIO register structre
typedef struct{
    __IO uint32_t MODER;   // Mode register
    __IO uint32_t OTYPER;  // Output type
    __IO uint32_t OSPEEDR; // Speed
    __IO uint32_t PUPDR;   // Pull-up/pull-down
    __I  uint32_t IDR;     // Input data
    __IO uint32_t ODR;     // Output data
    __IO uint32_t BSRR;    // Bit set/reset
    __IO uint32_t LCKR;    // Configuration lock
    __IO uint32_t AFR[2];  // Alternate functions
} TS_GPIO_TypeDef;


//GPIOs pointer
#define GPIOA ((TS_GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((TS_GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC ((TS_GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD ((TS_GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE ((TS_GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF ((TS_GPIO_TypeDef *) GPIOF_BASE)

//--------------------//
//        UART        //
//--------------------//

//UASRT peripheral base address
#define C_USART1_BASE            (C_APB2PERIPH_BASE + 0x3800)

//USART register structre
typedef struct{
    __IO uint32_t CR1;     // Control register 1
    __IO uint32_t CR2;     // Control register 2
    __IO uint32_t CR3;     // Control register 3
    __IO uint32_t BRR;     // Baud rate register
    __IO uint32_t GTPR;    // Guard time and prescaler
    __IO uint32_t RTOR;    // Receiver timeout
    __IO uint32_t RQR;     // Request register
    __IO uint32_t ISR;     // Interrupt and status register
    __IO uint32_t ICR;     // Interrupt flag clear register
    __I  uint32_t RDR;     // Receive data register
    __IO uint32_t TDR;     // Transmit data register
} TS_USART_TypeDef;

//USART1 pointer
#define USART1 ((TS_USART_TypeDef *) C_USART1_BASE)

//Controle register bits (CR)
#define C_USART_CR_RE         (1U << 2)
#define C_USART_CR_TE         (1U << 3)
#define C_USART_CR_UE         (1U << 13)

//Interrupt register status bits (ISR)
#define C_USART_ISR_FE        (1U << 1) // Farming error
#define C_USART_ISR_NE        (1U << 2) // Noise error
#define C_USART_ISR_ORE       (1U << 3) // Overrun error  
#define C_USART_ISR_RXNE      (1U << 5) // Read date register not empty
#define C_USART_ISR_TC        (1U << 6) // Transmission complete
#define C_USART_ISR_TXE       (1U << 7) // Transmit data regisyter empty

#endif

//--------------------//
//         SCB        //
//--------------------//

// SCB : System Control Block
#define C_SCB_BASE          (0xE000ED00UL) // SCB base address

typedef struct 
{
    __I  uint32_t CPUID;    // 0x000 CPU ID Base Register
    __IO uint32_t ICSR;     // 0x004 Interrupt Control and State Register
    __IO uint32_t VTOR;     // 0x008 Vector Table Offset Register
    __IO uint32_t AIRCR;    // 0x00C Application Interrupt and Reset Control Register 
    __IO uint32_t SCR;      // 0x010 System Control Register
    __IO uint32_t CCR;      // 0x014 Configuration and Control Register
    __IO uint8_t  SHP[12];  // 0x018 System Handlers Priority Registers (4-7, 8-11, 12-15)
    __IO uint32_t SHCSR;    // 0x024 System Handler Control and State Register
    __IO uint32_t CFSR;     // 0x028 Configurable Fault Status Register
    __IO uint32_t HFSR;     // 0x02C HardFault Status Register
    __IO uint32_t DFSR;     // 0x030 Debug Fault Status Register
    __IO uint32_t MMFAR;    // 0x034 MemManage Fault Address Register
    __IO uint32_t BFAR;     // 0x038 BusFault Address Register
    __IO uint32_t AFSR;     // 0x03C Auxiliary Fault Status Register
} TS_SCB_TypeDef;

#define SCB ((TS_SCB_TypeDef *) C_SCB_BASE);