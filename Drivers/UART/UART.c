#include <stdint.h>
#include "STM32F3xx.h"
#include "UART.h"
#include "GPIO.h"
#include <stddef.h>

// ================= Internal Helpers =================
void UART_SetBaudRate(uint32_t baud)
{
    USART1->BRR = SystemCoreClock / baud;
}
// ===================================================

void UART_Init(void) 
{
    // 1. Enable USART1 and GPIOA clocks
    RCC->AHBENR |= C_RCC_AHBENR_GPIOAEN;    // GPIO clock
    RCC->APB2ENR |= C_RCC_APB2ENR_USART1EN; // UART1 clock
    

    // 2. Configure PA9 (TX) and PA10 (RX) as Alternate Function
    GPIO_InitPort(GPIOA);

    GPIO_Config(GPIOA, 9, E_GPIO_MODE_AF, E_GPIO_OTYPE_PP, E_GPIO_SPEED_HIGH, E_GPIO_NPULL);
    GPIO_Config(GPIOA, 10, E_GPIO_MODE_AF, E_GPIO_OTYPE_PP, E_GPIO_SPEED_HIGH, E_GPIO_NPULL);
    GPIO_Set_AF(GPIOA, 9,  C_GPIO_AF_USART1);
    GPIO_Set_AF(GPIOA, 10, C_GPIO_AF_USART1);

    // 3. Configure USART1
    USART1->CR1 = 0;                                    // Reset control register
    UART_SetBaudRate(115200U);                          // Baud = 115200 @ 72 MHz
    USART1->CR1 |= (C_USART_CR1_TE | C_USART_CR1_RE);   // Enable TX and RX
    USART1->CR1 |= C_USART_CR1_UE;                      // Enable USART
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
uint32_t UART_Receive(char *buffer, uint32_t len, uint32_t timeout) 
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