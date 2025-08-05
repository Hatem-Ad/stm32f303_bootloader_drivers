#ifndef UART_H
#define UART_H

void UART_Init(void);
void uart_send_char(char c);
char uart_receive_char(void);
uint32_t UART_Received(uint8_t *buffer, uint32_t len);
void UART_SendString(const char *str);

#endif
