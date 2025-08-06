#ifndef STM32F3xx_H
#define STM32F3xx_H

#include <stdint.h>


#define PERIPH_BASE            ((uint32_t) 0x40000000)
#define AHBPERIPH_BASE         (PERIPH_BASE + 0x20000)
#define APB1PERIPH_BASE        (PERIPH_BASE + 0x00000)
#define APB2PERIPH_BASE        (PERIPH_BASE + 0x10000)



//--------------------//
//        RCC         //
//--------------------//

//RCC base address
#define RCC_BASE               (AHBPERIPH_BASE + 0x1000)

// Peripheral activition bit
#define RCC_APB2ENR_USART1EN   (1U << 14) // Enable USART clock (APB2 bus)

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

//RCC AHBENR bits
#define RCC_AHBENR_GPIOAEN   (1U << 17) // Bit 17: IO port A clock enable 
#define RCC_AHBENR_GPIOBEN   (1U << 18) // Bit 17: IO port A clock enable 
#define RCC_AHBENR_GPIOCEN   (1U << 19) // Bit 17: IO port A clock enable 
#define RCC_AHBENR_GPIODEN   (1U << 20) // Bit 17: IO port A clock enable 
#define RCC_AHBENR_GPIOEEN   (1U << 21) // Bit 17: IO port A clock enable 
#define RCC_AHBENR_GPIOFEN   (1U << 22) // Bit 17: IO port A clock enable 




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
#define GPIOB_BASE             (AHBPERIPH_BASE + 0x0400)
#define GPIOC_BASE             (AHBPERIPH_BASE + 0x0800)
#define GPIOD_BASE             (AHBPERIPH_BASE + 0x0C00)
#define GPIOE_BASE             (AHBPERIPH_BASE + 0x1000)
#define GPIOF_BASE             (AHBPERIPH_BASE + 0x1400)

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

//GPIOA pointer
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOD ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOE ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOF ((GPIO_TypeDef *) GPIOA_BASE)







//--------------------//
//        UART        //
//--------------------//

//UASRT peripheral base address
#define USART1_BASE            (APB2PERIPH_BASE + 0x3800)

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
} USART_TypeDef;

//USART1 pointer
#define USART1 ((USART_TypeDef *) USART1_BASE)

//Controle register bits (CR)
#define USART_CR_TE         (1U << 3)
#define USART_CR_RE         (1U << 2)
#define USART_CR_UE         (1U << 13)

//Interrupt register status bits (ISR)
#define USART_ISR_TXE       (1U << 7)
#define USART_ISR_RXNE      (1U << 5)


#endif