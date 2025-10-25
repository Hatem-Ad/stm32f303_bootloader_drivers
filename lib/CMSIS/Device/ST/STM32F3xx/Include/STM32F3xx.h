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

extern uint32_t SystemCoreClock = 8000000U;  // default HSI frequency before PLL setup

//--------------------//
//        RCC         //
//--------------------//

/* Base address of Reset and Clock Control (RCC) registers */
#define C_RCC_BASE               (C_AHBPERIPH_BASE + 0x1000)

/* RCC register layout */
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

/* Pointer to RCC registers */
#define RCC ((TS_RCC_TypeDef *) C_RCC_BASE)

/*-------------------- AHBENR Bits --------------------*/
#define C_RCC_AHBENR_GPIOAEN      (1U << 17) // IO port A clock enable 
#define C_RCC_AHBENR_GPIOBEN      (1U << 18) // IO port B clock enable 
#define C_RCC_AHBENR_GPIOCEN      (1U << 19) // IO port C clock enable 
#define C_RCC_AHBENR_GPIODEN      (1U << 20) // IO port D clock enable 
#define C_RCC_AHBENR_GPIOEEN      (1U << 21) // IO port E clock enable 
#define C_RCC_AHBENR_GPIOFEN      (1U << 22) // IO port F clock enable 

/*-------------------- Controle register Bits --------------------*/
#define C_RCC_CR_HSION            (1U << 0)   // Enable HSI
#define C_RCC_CR_HSIRDY           (1U << 1)   // HSI ready flag
#define C_RCC_CR_PLLON            (1U << 24)  // Enable PLL
#define C_RCC_CR_PLLRDY           (1U << 25)  // PLL ready flag

/*-------------------- Configure register Bits --------------------*/
#define C_RCC_CFGR_SW_Pos         0U
#define C_RCC_CFGR_SW_Msk         (0x3U << C_RCC_CFGR_SW_Pos)
#define C_RCC_CFGR_SW_HSI         (0x0U << C_RCC_CFGR_SW_Pos)
#define C_RCC_CFGR_SW_PLL         (0x2U << C_RCC_CFGR_SW_Pos)

#define C_RCC_CFGR_SWS_Pos        2U
#define C_RCC_CFGR_SWS_Msk        (0x3U << C_RCC_CFGR_SWS_Pos)
#define C_RCC_CFGR_SWS_HSI        (0x0U << C_RCC_CFGR_SWS_Pos)
#define C_RCC_CFGR_SWS_PLL        (0x2U << C_RCC_CFGR_SWS_Pos)

/* PLL configuration fields */
#define C_RCC_CFGR_PLLSRC_Pos     16U
#define C_RCC_CFGR_PLLSRC         (1U << C_RCC_CFGR_PLLSRC_Pos)
#define C_RCC_CFGR_PLLXTPRE       (1U << 17)
#define C_RCC_CFGR_PLLMUL_Pos     18U
#define C_RCC_CFGR_PLLMUL_Msk     (0xFU << C_RCC_CFGR_PLLMUL_Pos)

#define C_RCC_CFGR_PLLSRC_HSI_Div2  (0U << C_RCC_CFGR_PLLSRC_Pos) // HSI/2 input
#define C_RCC_CFGR_PLLMUL18         (9U << C_RCC_CFGR_PLLMUL_Pos) // x18 = 72 MHz

/* Combined PLL masks */
#define C_RCC_CFGR_PLL_MASK   (C_RCC_CFGR_PLLSRC | C_RCC_CFGR_PLLXTPRE | C_RCC_CFGR_PLLMUL_Msk)
#define C_RCC_CFGR_PLL_HSIx18 (C_RCC_CFGR_PLLSRC_HSI_Div2 | C_RCC_CFGR_PLLMUL18)

/*-------------------- CSR Bits (Low Speed Internal oscillator for IWDG) --------------------*/
#define C_RCC_CSR_LSION           (1U << 0)
#define C_RCC_CSR_LSIRDY          (1U << 1)

/*-------------------- Peripheral Clock Enable Bits --------------------*/
#define C_RCC_APB2ENR_USART1EN    (1U << 14) // Enable USART1 (APB2)

//--------------------//
//       FLASH        //
//--------------------//

/* Base address of Flash interface registers */
#define C_FLASH_BASE  (0x40022000UL)

/* Flash register structure */
typedef struct {
    __IO uint32_t ACR;      // 0x00: Access control register
    __IO uint32_t KEYR;     // 0x04: Key register
    __IO uint32_t OPTKEYR;  // 0x08: Option key register
    __IO uint32_t SR;       // 0x0C: Status register
    __IO uint32_t CR;       // 0x10: Control register
    __IO uint32_t AR;       // 0x14: Address register
         uint32_t RESERVED; // 0x18: Reserved
    __I  uint32_t OBR;      // 0x1C: Option byte register
    __I  uint32_t WRPR;     // 0x20: Write protection register
} TS_FLASH_TypeDef;

/* Pointer to FLASH registers */
#define FLASH ((TS_FLASH_TypeDef *) C_FLASH_BASE)

/*-------------------- Flash Keys --------------------*/
#define C_FLASH_KEY1   (0x45670123UL)
#define C_FLASH_KEY2   (0xCDEF89ABUL)

/*-------------------- FLASH_CR Bits --------------------*/
#define C_FLASH_CR_PG          (1U << 0)  // Programming mode
#define C_FLASH_CR_PER         (1U << 1)  // Page erase
#define C_FLASH_CR_MER         (1U << 2)  // Mass erase (optional)
#define C_FLASH_CR_OPTPG       (1U << 4)  // Option byte programming
#define C_FLASH_CR_OPTER       (1U << 5)  // Option byte erase
#define C_FLASH_CR_START       (1U << 6)  // Start operation
#define C_FLASH_CR_LOCK        (1U << 7)  // Lock flash control register
#define C_FLASH_CR_EOPIE       (1U << 12) // End of operation interrupt enable
#define C_FLASH_CR_ERRIE       (1U << 10) // Error interrupt enable

/*-------------------- FLASH_SR Bits --------------------*/
#define C_FLASH_SR_BSY         (1U << 0)  // Busy flag
#define C_FLASH_SR_PGERR       (1U << 2)  // Programming error
#define C_FLASH_SR_WRPERR      (1U << 4)  // Write protection error
#define C_FLASH_SR_EOP         (1U << 5)  // End of operation flag

/*-------------------- FLASH_ACR Bits --------------------*/
#define C_FLASH_ACR_LATENCY_Pos    0U
#define C_FLASH_ACR_LATENCY_Msk    (0x7U << C_FLASH_ACR_LATENCY_Pos)
#define C_FLASH_ACR_LATENCY_0WS    (0x0U << C_FLASH_ACR_LATENCY_Pos)
#define C_FLASH_ACR_LATENCY_1WS    (0x1U << C_FLASH_ACR_LATENCY_Pos)
#define C_FLASH_ACR_LATENCY_2WS    (0x2U << C_FLASH_ACR_LATENCY_Pos)

#define C_FLASH_ACR_PRFTBE         (1U << 4)   // Prefetch buffer enable
#define C_FLASH_ACR_PRFTBS         (1U << 5)   // Prefetch buffer status (read-only)

/*-------------------- Convenient Aliases --------------------*/
#define C_FLASH_ACR_LATENCY        C_FLASH_ACR_LATENCY_Msk
#define C_FLASH_ACR_LATENCY_2      C_FLASH_ACR_LATENCY_2WS

// Flash layout (STM32F303xC)
#define C_FLASH_BASE_ADDR     (0x08000000UL)
#define C_FLASH_BOOT_SIZE     (16U * 1024U)          // 16 KB bootloader
#define C_FLASH_APP_BASE      (C_FLASH_BASE_ADDR + C_FLASH_BOOT_SIZE)  // 0x08004000

// Device specifics
#define C_FLASH_PAGE_SIZE     (2048U)                // 2 KB per page on F303xC
#define C_FLASH_TOTAL_SIZE    (256U * 1024U)         // 256 KB total (F303VC)

//--------------------//
//        GPIO        //
//--------------------//

//GPIO peripheral base address
#define GPIOA_BASE                  (C_AHBPERIPH_BASE + 0x0000)
#define GPIOB_BASE                  (C_AHBPERIPH_BASE + 0x0400)
#define GPIOC_BASE                  (C_AHBPERIPH_BASE + 0x0800)
#define GPIOD_BASE                  (C_AHBPERIPH_BASE + 0x0C00)
#define GPIOE_BASE                  (C_AHBPERIPH_BASE + 0x1000)
#define GPIOF_BASE                  (C_AHBPERIPH_BASE + 0x1400)

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
#define C_USART1_BASE               (C_APB2PERIPH_BASE + 0x3800)

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
#define C_USART_CR_RE               (1U << 2)
#define C_USART_CR_TE               (1U << 3)
#define C_USART_CR_UE               (1U << 13)

//Interrupt status register bits (ISR)
#define C_USART_ISR_FE              (1U << 1) // Farming error
#define C_USART_ISR_NE              (1U << 2) // Noise error
#define C_USART_ISR_ORE             (1U << 3) // Overrun error  
#define C_USART_ISR_RXNE            (1U << 5) // Read date register not empty
#define C_USART_ISR_TC              (1U << 6) // Transmission complete
#define C_USART_ISR_TXE             (1U << 7) // Transmit data regisyter empty

#define C_USART_CR1_RE_Pos          2U   // Receiver enable
#define C_USART_CR1_TE_Pos          3U   // Transmitter enable
#define C_USART_CR1_UE_Pos          13U  // USART enable

#define C_USART_CR1_RE              (1U << C_USART_CR1_RE_Pos)
#define C_USART_CR1_TE              (1U << C_USART_CR1_TE_Pos)
#define C_USART_CR1_UE              (1U << C_USART_CR1_UE_Pos)

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

#define SCB ((TS_SCB_TypeDef *) C_SCB_BASE)

//--------------------//
//       SysTick      //
//--------------------//

#define C_SysTick_BASE      (0xE000E010UL)

typedef struct
{
    __IO uint32_t CTRL;  // Control and status register   0x00
    __IO uint32_t LOAD;  // Reload value register         0x04
    __IO uint32_t VAL;   // Current value Register        0x08
    __I  uint32_t CALIB; // Calibration value register    0x0C
} TS_SysTick_TypeDef;

#define SysTick ((TS_SysTick_TypeDef *) C_SysTick_BASE)

#define C_SysTick_CTRL_ENABLE_Pos       0U
#define C_SysTick_CTRL_TICKINT_Pos      1U
#define C_SysTick_CTRL_CLKSOURCE_Pos    2U
#define C_SysTick_CTRL_COUNTFLAG_Pos    16U

#define C_SysTick_CTRL_ENABLE_Msk       (1UL << C_SysTick_CTRL_ENABLE_Pos)
#define C_SysTick_CTRL_TICKINT_Msk      (1UL << C_SysTick_CTRL_TICKINT_Pos)
#define C_SysTick_CTRL_CLKSOURCE_Msk    (1UL << C_SysTick_CTRL_CLKSOURCE_Pos)
#define C_SysTick_CTRL_COUNTFLAG_Msk    (1UL << C_SysTick_CTRL_COUNTFLAG_Pos)

//--------------------//
//        IWDG        //
//--------------------//

#define C_IWDG_BASE         (0x40003000UL)

typedef struct 
{
    __IO uint32_t KR;   // 0x00 Key register
    __IO uint32_t PR;   // 0x04 Prescaler
    __IO uint32_t RLR;  // 0x08 Reload
    __IO uint32_t SR;   // 0x0C Status
    __IO uint32_t WINR; // 0x10 Window (unused in this base line v1.0)
} TS_IWDG_TypeDef;

#define IWDG ((TS_IWDG_TypeDef *) C_IWDG_BASE)

// KR keys
#define C_IWDG_KR_KEY_WRITE     (0x5555U)
#define C_IWDG_KR_KEY_RELOAD    (0xAAAAU)
#define C_IWDG_KR_KEY_ENABLE    (0xCCCCU)

// PR (Prescaler) codes : div = 4,8,16,32,46,128,256
#define C_IWDG_PR_DIV4          (0U)
#define C_IWDG_PR_DIV8          (1U)
#define C_IWDG_PR_DIV16         (2U)
#define C_IWDG_PR_DIV32         (3U)
#define C_IWDG_PR_DIV64         (4U)
#define C_IWDG_PR_DIV128        (5U)
#define C_IWDG_PR_DIV256        (6U)

// SR flags
#define C_IWDG_SR_PVU           (1U << 0) // PR update ongoing
#define C_IWDG_SR_RVU           (1U << 1) // RLR update ongoing

// LSI nominal
#define C_LSI_HZ                (40000U)  // 40 KHz typical


#endif