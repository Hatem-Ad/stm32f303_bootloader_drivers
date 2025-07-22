#include "UART.h"
#include "stdint.h"

void UART_Init(void) {
    // TODO: Init USART1 or USART2
}

void uart_send_char(char c) {
    // TODO: Send character via UART
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
