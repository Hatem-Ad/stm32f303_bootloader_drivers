#ifndef GPIO_H
#define GPIO_H

#include <STM32F3xx.h>

// Bits definitions for GPIO registers
#define C_GPIO_MODER_BITS_PER_PIN     0x2U // Number of bits by moder pin
#define C_GPIO_MODER_MASK             0x3U // Two bits per pin (11b)
#define C_GPIO_MODE_AF                0x2U // Alternant function mode

#define C_GPIO_OTYPER_BITS_PER_PIN    0x1U // Number of bit by otyper pin
#define C_GPIO_OTYPER_MASK            0x1U // One bit per pin

#define C_GPIO_OSPEEDER_BITS_PER_PIN  0x2U // Number of bits by ospeeder pin
#define C_GPIO_OSPEEDER_MASK          0x3U // Two bits per pin (11b)

#define C_GPIO_PUPDR_BITS_PER_PIN     0x2U // Number of bits by pipdr pin
#define C_GPIO_PUPDR_MASK             0x3U // Two bits per pin (11b)

#define C_GPIO_AFR_BITS_PER_PIN       0x4U // 4 bits per pin in AFR
#define C_GPIO_AFR_MASK               0xFU // Mask = 4 bits
#define C_GPIO_AFR_PINS_PER_REG       0x8U // AFRL = pins 0-7, AFRH = pins 8-15
#define C_GPIO_AF_USART1              0x7U // USART1 function active

#define C_GPIO_PIN9                   0x9U // Pin number 9
#define C_GPIO_PIN10                  0xAU // Pin number 10





//GPIO Modes
typedef enum{
    E_GPIO_MODE_INPUT  = 0x0,
    E_GPIO_MODE_OUTPUT = 0x1,
    E_GPIO_MODE_AF     = 0x2,
    E_GPIO_MODE_ANALOG = 0x3
} TE_GPIO_mode_t;


typedef enum {
    E_GPIO_OTYPE_PP = 0x0, // Push-Pull
    E_GPIO_OTYPE_OD = 0x1  // Open-Drain
} TE_GPIO_otype_t;

typedef enum {
    E_GPIO_SPEED_LOW    = 0,
    E_GPIO_SPEED_MEDIUM = 1,
    E_GPIO_SPEED_HIGH   = 2
} TE_GPIO_speed_t;

typedef enum {
    E_GPIO_NPULL    = 0,
    E_GPIO_PULLUP   = 1,
    E_GPIO_PULLDOWN = 2
} TE_GPIO_pull_t;

//GPIO pins declaration
#define C_GPIO_Pin_0    0
#define C_GPIO_Pin_1    1
#define C_GPIO_Pin_2    2
#define C_GPIO_Pin_3    3
#define C_GPIO_Pin_4    4
#define C_GPIO_Pin_5    5
#define C_GPIO_Pin_6    6
#define C_GPIO_Pin_7    7
#define C_GPIO_Pin_8    8
#define C_GPIO_Pin_9    9
#define C_GPIO_Pin_10   10


/**
 * @brief Initialize all used GPIO ports.
 *
 * This function enables the peripheral clock for every GPIO port
 * that will be used in the application (e.g., GPIOA–GPIOE).
 * It should be called once at system startup before configuring any pins.
 */
void GPIO_Init(void);

/**
 * @brief Initialize a specific GPIO port.
 *
 * This function enables the peripheral clock for the selected GPIO port.
 * Typically used internally by GPIO_Init(), but can also be called directly
 * to enable a specific port.
 *
 * @param port Pointer to the GPIO port (e.g., GPIOA, GPIOB, ...).
 */
void GPIO_InitPort(TS_GPIO_TypeDef *port);


/**
 * @brief Write a digital state (HIGH or LOW) to a GPIO pin.
 *
 * @param port  Pointer to the GPIO port.
 * @param pin   Pin number (0–15).
 * @param state State of the pin: 0 = LOW, 1 = HIGH.
 */
void GPIO_Write(TS_GPIO_TypeDef   *port, 
                uint8_t            pin, 
                uint8_t            state);

/**
 * @brief Toggle the current output state of a GPIO pin.
 *
 * @param port Pointer to the GPIO port.
 * @param pin  Pin number (0–15).
 */
void GPIO_Toggle(TS_GPIO_TypeDef  *port, 
                 uint8_t           pin);

/**
 * @brief Configure the alternate function of a GPIO pin.
 *
 * @param port Pointer to the GPIO port.
 * @param pin  Pin number (0–15).
 * @param af   Alternate function number (0–15).
 */
void GPIO_Set_AF(TS_GPIO_TypeDef  *port, 
                 uint8_t           pin,
                 uint8_t           af);

/**
 * @brief Read the digital input state of a GPIO pin.
 *
 * @param port Pointer to the GPIO port.
 * @param pin  Pin number (0–15).
 * @return     1 if the pin is HIGH, 0 if the pin is LOW.
 */
uint8_t GPIO_Read(TS_GPIO_TypeDef *port, 
                  uint8_t          pin);

/**
 * @brief Configure the mode, type, speed, and pull-up/down of a GPIO pin.
 *
 * @param port  Pointer to the GPIO port.
 * @param pin   Pin number (0–15).
 * @param mode  Pin mode (input, output, alternate function, analog).
 * @param otype Output type (push-pull or open-drain).
 * @param speed Output speed (low, medium, high, very high).
 * @param pull  Pull-up/pull-down configuration (none, pull-up, pull-down).
 */
void GPIO_Config(TS_GPIO_TypeDef   *port, 
                 uint8_t            pin, 
                 TE_GPIO_mode_t     mode,
                 TE_GPIO_otype_t    otype,
                 TE_GPIO_speed_t    speed,
                 TE_GPIO_pull_t     pull);

#endif
