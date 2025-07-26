#include "UART.h"
#include "stdint.h"

void UART_Init(void) {
    
    //Enble USART1 clock and GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    //Configure PA9 (TX) and PA10(RX)
    GPIOA->MODER &= ~((3U << (9 *2)) | (3U << (10 *2)));
    GPIOA->MODER |= (2U << (9 * 2)) | (2U << (10 * 2)); //Alternate function

    GPIOA->AFR[1] |= (7U << ((9 - 8) * 4)) | (7U << ((10 - 8) * 4)); // AF7

    //Configure USART1 (9600 bauds, 8N1)
    USART1->BRR = 8000000 / 9600;
    USART1->CR1 = USART_CR_TE | USART_CR_RE | USART_CR_UE;

}

void UART_SendString(const char *str) {
    
    while(*str){
        while (!(USART1->ISR & USART_ISR_TXE));
        USART1->TDR = *str++;
    }
}

// Read a chnik of at most len bytes
char UART_Received(uint8_t *buffer, uint32_t len) {
    uint32_t count = 0;

    while (count < len)
    {
        if (UART_Available())
        {
            //Verifiy if one bytes is dispo
            buffer[count++] = UART_ReadByte();
        }
        else
        {
            break; // No more data
        }
    }
    

    return 0;
}
