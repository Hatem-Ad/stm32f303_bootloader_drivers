#ifndef GPIO_H
#define GPIO_H

// Bits definitions for GPIO registers
#define C_GPIO_MODER_BITS_PER_PIN     0x2U
#define C_GPIO_MODER_MASK             0x3U // Two bits per pin (11b)

#define C_GPIO_OTYPER_BITS_PER_PIN    0x1U
#define C_GPIO_OTYPER_MASK            0x1U // One bit per pin

#define C_GPIO_OSPEEDER_BITS_PER_PIN  0x2U
#define C_GPIO_OSPEEDER_MASK          0x3U // Two bits per pin (11b)

#define C_GPIO_PUPDR_BITS_PER_PIN     0x2U
#define C_GPIO_PUPDR_MASK             0x3U // Two bits per pin (11b)

#define C_GPIO_AFR_BITS_PER_PIN       0x4U // 4 bits per pin in AFR
#define C_GPIO_AFR_MASK               0xFU // Mask = 4 bits
#define C_GPIO_AFR_PINS_PER_REG       0x8U // AFRL = pins 0-7, AFRH = pins 8-15

//GPIO Modes
typedef enum{
    GPIO_MODE_INPUT  = 0x0,
    GPIO_MODE_OUTPUT = 0x1,
    GPIO_MODE_AF     = 0x2,
    GPIO_MODE_ANALOG = 0x3
} TE_GPIO_mode_t;


typedef enum {
    GPIO_OTYPE_PP = 0x0, // Push-Pull
    GPIO_OTYPE_OD = 0x1  // Open-Drain
} TE_GPIO_otype_t;

typedef enum {
    GPIO_SPEED_LOW    = 0,
    GPIO_SPEED_MEDIUM = 1,
    GPIO_SPEED_HIGH   = 2
} TE_GPIO_speed_t;

typedef enum {
    GPIO_NPULL    = 0,
    GPIO_PULLUP   = 1,
    GPIO_PULLDOWN = 2
} TE_GPIO_pull_t;


/**
 * @brief Initialize a GPIO pin.
 * 
 * This function prepares the GPIO port and pin for use.
 * Typically used to enable the clock or reset a pin to a default state.
 *
 * @param port Pointer to the GPIO port (e.g., GPIOA, GPIOB, ...).
 * @param pin  Pin number (0–15).
 */
void GPIO_Init(TS_GPIO_TypeDef    *port, 
               uint8_t             pin);

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
