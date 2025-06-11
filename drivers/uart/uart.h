#ifndef UART_H
#define UART_H

void uart_init(void);
void uart_send_char(char c);
char uart_receive_char(void);

#endif
