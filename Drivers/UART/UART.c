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
    GPIOA->AFR[1] &= ~((C_GPIO_AFR_MASK << ((C_GPIO_PIN9 % C_GPIO_AFR_PINS_PER_REG) * C_GPIO_AFR_BITS_PER_PIN)) | 
                       (C_GPIO_AFR_MASK << ((C_GPIO_PIN10 % C_GPIO_AFR_PINS_PER_REG) * C_GPIO_AFR_BITS_PER_PIN))); // clear


    GPIOA->AFR[1] |= ((C_GPIO_AF_USART1 << ((C_GPIO_PIN9  % C_GPIO_AFR_PINS_PER_REG) * C_GPIO_AFR_BITS_PER_PIN)) |
                      (C_GPIO_AF_USART1 << ((C_GPIO_PIN10 % C_GPIO_AFR_PINS_PER_REG) * C_GPIO_AFR_BITS_PER_PIN))); // active usart in pins 9 and 10 / AF7

    // -------- Configure USART1 (9600 bauds, 8N1) --------
    USART1->BRR = (C_APB2_CLOCK + C_UART_BAUD / 2)/ C_UART_BAUD; // (to get 833.833 => 834 => Baud ≈ 9603 inplace of 833.333 => 833 => Baud ≈ 9595)
    USART1->CR1 = C_USART_CR_TE | C_USART_CR_RE | C_USART_CR_UE;

}

void UART_SendString(const char *str) 
{
    if (str == NULL) return; // Safty check

    while(*str != '\0')
    {
        // Wait until TXE (Transmit Data Register Emty)
        while (!(USART1->ISR & C_USART_ISR_TXE));

        // Write chharachter into TDR
        USART1->TDR = (uint8_t)(*str++);
    }

    // Wait intil TC is set (Transmission compltee)
    while (!(USART1->ISR & C_USART_ISR_TC));
    
}

// Read a chnuk of at most len bytesUSART1 ...
uint32_t UART_Received(char *buffer, uint32_t len, uint32_t timeout) 
{
    uint32_t i = 0;
    uint32_t counter = 0;

    while (i < len) 
    {
        // Wait until RXNE flag is set or timeout expires
        while (!(USART1->ISR & C_USART_ISR_RXNE))
        {
            if (++counter > timeout)
            {
                return i; // return how many bytes were recieved before timeout
            }
        }

        // Check for errors before reading
        if (USART1->ISR & (C_USART_ISR_ORE | C_USART_ISR_FE | C_USART_ISR_NE))
        {
            // Clear error flags by reding ISR then RDR
            volatile uint32_t tmp;
            tmp = USART1->ISR; // For read the ISR reg
            (void)tmp; // For eliminate unused warning by the complier
            tmp = USART1->RDR; // For read the register data read and clear the interuptions.
            (void)tmp; // For eliminate unused warning by the complier
            
            return i; // stop an error
        }

        buffer[i++] = (char)(USART1->RDR & 0xFF); // read reiceved data (just the lowest 8 byts, the others is reserved)
        counter = 0; // Reset timeout counter after each succeful reception
    }
    return i; // Number of bytes successfully recieved
}


void UART_send_char(char c)
{
    uint32_t timeout = UART_TIMEOUT;
    // Wait until the transmit data register is empty (TXE = 1)
    while (!(USART1->ISR & C_USART_ISR_TXE))
    {
        if(--timeout == 0U)
        {
            // Timeout occurred -> exit or handle error
            return;
        }
    }

    // Write the character to the Transmit Data Register to send it
    USART1->TDR = (uint8_t)c;
}

char UART_receive_char(void) 
{
    uint32_t timeout = UART_TIMEOUT;

    // Wait until the receive data register is not empty (RXNE = 1)
    while (!(USART1->ISR & C_USART_ISR_RXNE))
    {
        if (--timeout == 0U)
        {
            // Timeout occurred -> return an error value
            return (char)-1;
        }
    }

    // Read and return the received character from Receive Data Register
    return (char)(USART1->RDR & 0xFFU);
}