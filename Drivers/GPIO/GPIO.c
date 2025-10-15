#include <stdint.h>
#include "GPIO.h"
#include "STM32F3xx.h"

// ================= Internal Helpers =================
static GPIO_EnableClock(TS_GPIO_TypeDef   *port) 
{ 
    //Enable Clock for selcted port
    if (port == GPIOA) RCC->AHBENR |= C_RCC_AHBENR_GPIOAEN;
    else if (port == GPIOB) RCC->AHBENR |= C_RCC_AHBENR_GPIOBEN;
    else if (port == GPIOC) RCC->AHBENR |= C_RCC_AHBENR_GPIOCEN;
    else if (port == GPIOD) RCC->AHBENR |= C_RCC_AHBENR_GPIODEN;
    else if (port == GPIOE) RCC->AHBENR |= C_RCC_AHBENR_GPIOEEN;
    else if (port == GPIOF) RCC->AHBENR |= C_RCC_AHBENR_GPIOFEN;
}
// ===================================================

// Initialize one port (enable its clock)
void GPIO_InitPort(TS_GPIO_TypeDef *port)
{
    GPIO_EnableClock(port);
}

void GPIO_Init(void)
{
    TS_GPIO_TypeDef *ports[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE};
    uint8_t count = sizeof(ports)/sizeof(ports[0]);
    for (uint8_t i = 0; i < count; i++)
    {
        GPIO_InitPort(ports[i]);
    }
}

void GPIO_Config(TS_GPIO_TypeDef   *port, 
                 uint8_t            pin, 
                 TE_GPIO_mode_t     mode,
                 TE_GPIO_otype_t    otype,
                 TE_GPIO_speed_t    speed,
                 TE_GPIO_pull_t     pull)
{ 
    // -------- Mode (MODER) --------
    port->MODER &= ~(C_GPIO_MODER_MASK << (pin * C_GPIO_MODER_BITS_PER_PIN)); // Clear the 2 bits for the pin
    port->MODER |= ((mode & 0x3U) << (pin * 2)); // Set the mode

    // -------- Output Type (OTYPER) --------
    port->OTYPER &= ~(C_GPIO_OTYPER_MASK << pin); // Clear the bit for the pin
    port->OTYPER |= ((otype & C_GPIO_OTYPER_MASK) << pin); // Set Push-pull (0) or Open-drain (1)

    // -------- Output Speed (OSPEEDR) --------
    port->OSPEEDR &= ~(C_GPIO_OSPEEDER_MASK << (pin * C_GPIO_OSPEEDER_BITS_PER_PIN)); // Clear 2 bits
    port->OSPEEDR |=((speed & C_GPIO_OSPEEDER_MASK) << (pin * C_GPIO_OSPEEDER_BITS_PER_PIN)); // Clear 2 bits

    // -------- Pull-up / Pull-down (PUPDR) --------
    port->PUPDR &= ~(C_GPIO_PUPDR_MASK << (pin * C_GPIO_PUPDR_BITS_PER_PIN)); // Clear 2 bits
    port->PUPDR |= ((pull & C_GPIO_PUPDR_MASK) << (pin * C_GPIO_PUPDR_BITS_PER_PIN)); // Clear 2 bits

}

//This function reads the input data register (IDR) of X Port  and checks the state
//of the requested pin. It returns the logical state (1 or 0) of the pin.
uint8_t GPIO_Read(TS_GPIO_TypeDef *port, 
                  uint8_t          pin)
{
    return ((port->IDR & (1U << pin)) != 0U) ? 1U : 0U;
}

void GPIO_Write(TS_GPIO_TypeDef *port, 
                uint8_t          pin, 
                uint8_t          state)
{
    if(state){
        port->BSRR = (1U << pin); //Set pin hihg
    } else {
        port->BSRR = (1U << (pin + 16)); // set pin low
    }
}

//This function toggles the state of a given output pin on GPIOX.
void GPIO_Toggle(TS_GPIO_TypeDef *port, 
                 uint8_t          pin)
{
    if(port->ODR & (1U << pin))
    {
        // if pin is high => reset it
        port->BSRR = (1U << (pin + 16));
    }
    else
    {
        // if pin is low set it
        port->BSRR = (1U << pin);
    }
}

void GPIO_Set_AF(TS_GPIO_TypeDef *port, uint8_t pin, uint8_t af)
{
    uint8_t afr_index = pin / C_GPIO_AFR_PINS_PER_REG;  // 0 : af register low / 1 : af registre high
    uint8_t afr_pos = (pin % C_GPIO_AFR_PINS_PER_REG) * C_GPIO_AFR_BITS_PER_PIN;

    // Clear old alternat function
    port->AFR[afr_index] &= ~(C_GPIO_AFR_MASK << afr_pos);

    // Set new alternat function
    port->AFR[afr_index] |= ((af & C_GPIO_AFR_MASK) << afr_pos);
}