#include <stdint.h>
#include "UART.h"
#include "GPIO.h"
#include "STM32F3xx.h"
#include <stddef.h>

void UART_Init(void) 
{
    
     // -------- Enable USART1 and GPIOA clocks --------
    RCC->APB2ENR |= C_RCC_APB2ENR_USART1EN;
    RCC->AHBENR |= C_RCC_AHBENR_GPIOAEN;

    // -------- Configure PA9 (TX) and PA10 (RX) as Alternate Function --------
    GPIOA->MODER &= ~((C_GPIO_MODER_MASK << (C_GPIO_PIN9 * C_GPIO_MODER_BITS_PER_PIN)) | 
                      (C_GPIO_MODER_MASK << (C_GPIO_PIN10 * C_GPIO_MODER_BITS_PER_PIN)));

    GPIOA->MODER |= (C_GPIO_MODE_AF << (C_GPIO_PIN9 * C_GPIO_MODER_BITS_PER_PIN)) | 
                    (C_GPIO_MODE_AF << (C_GPIO_PIN10 * C_GPIO_MODER_BITS_PER_PIN)); //Alternate function
    
    // -------- Select AF7 (USART1) for PA9/PA10 --------
    GPIOA->AFR[1] |= ~((C_GPIO_AFR_MASK << ((C_GPIO_PIN9 % C_GPIO_AFR_PINS_PER_REG) * C_GPIO_AFR_BITS_PER_PIN)) | 
                       (C_GPIO_AFR_MASK << ((C_GPIO_PIN10 % C_GPIO_AFR_PINS_PER_REG) * C_GPIO_AFR_BITS_PER_PIN))); // clear


    GPIOA->AFR[1] |= ((C_GPIO_AF_USART1 << ((C_GPIO_PIN9  % C_GPIO_AFR_PINS_PER_REG) * C_GPIO_AFR_BITS_PER_PIN)) |
                      (C_GPIO_AF_USART1 << ((C_GPIO_PIN10 % C_GPIO_AFR_PINS_PER_REG) * C_GPIO_AFR_BITS_PER_PIN))); // active usart in pins 9 and 10 / AF7

    // -------- Configure USART1 (9600 bauds, 8N1) --------
    USART1->BRR = C_APB2_CLOCK / 9600;
    USART1->CR1 = C_USART_CR_TE | C_USART_CR_RE | C_USART_CR_UE;

}

void UART_SendString(const char *str) 
{
    if (str == NULL) return; // Safty check

    while(*str != '/0')
    {
        // Wait until TXE (Transmit Data Register Emty)
        while (!(USART1->ISR & C_USART_ISR_TXE));

        // Write chharachter into TDR
        USART1->TDR = (uint8_t)(*str++);
    }

    // Wait intil TC is set (Transmission compltee)
    while (!(USART1->ISR & C_USART_ISR_TC))
    {
        /* code */
    }
    
}

// Read a chnuk of at most len bytesUSART1 ...
uint32_t UART_Received(uint8_t *buffer, uint32_t len) 
{
    uint32_t i = 0;

    while (i < len) {
        while (!(USART1->ISR & C_USART_ISR_RXNE));
        buffer[i++] = USART1->RDR;
    }
    return i;
}


void UART_send_char(char c)
{
    // Wait until the transmit data register is empty (TXE = 1)
    while (!(USART1->ISR & C_USART_ISR_TXE));

    // Write the character to the Transmit Data Register to send it
    USART1->TDR = c;
}

char UART_receive_char(void) 
{
    // Wait until the receive data register is not empty (RXNE = 1)
    while (!(USART1->ISR & C_USART_ISR_RXNE));

    // Read and return the received character from Receive Data Register
    return USART1->RDR;
}