#include <stdint.h>
#include "UART.h"
#include "STM32F3xx.h"

void UART_Init(void) 
{
    
    //Enble USART1 clock and GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    //Configure PA9 (TX) and PA10(RX)
    GPIOA->MODER &= ~((3U << (9 * 2)) | (3U << (10 * 2)));
    GPIOA->MODER |= (2U << (9 * 2)) | (2U << (10 * 2)); //Alternate function

    GPIOA->AFR[1] |= (7U << ((9 - 8) * 4)) | (7U << ((10 - 8) * 4)); // AF7

    //Configure USART1 (9600 bauds, 8N1)
    USART1->BRR = 8000000 / 9600;
    USART1->CR1 = USART_CR_TE | USART_CR_RE | USART_CR_UE;

}

void UART_SendString(const char *str) 
{
    
    while(*str){
        while (!(USART1->ISR & USART_ISR_TXE));
        USART1->TDR = *str++;
    }
}

// Read a chnuk of at most len bytesUSART1 ...
uint32_t UART_Received(uint8_t *buffer, uint32_t len) 
{
    uint32_t i = 0;
    while (i < len) {
        while (!(USART1->ISR & USART_ISR_RXNE));
        buffer[i++] = USART1->RDR;
    }
    return i;
}


void UART_send_char(char c)
{
    while (!(USART1->ISR & USART_ISR_TXE));
    USART1->TDR = c;
}

char UART_receive_char(void) 
{
    while (!(USART1->ISR & USART_ISR_RXNE));
    return USART1->RDR;
}