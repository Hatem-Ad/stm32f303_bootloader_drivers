#ifndef UART_H
#define UART_H


#define F_CPU           8000000U
#define UART_BAUD       9600U
#define C_APB2_CLOCK    8000000U

#define UART_TIMEOUT    1000000U


void UART_Init(void);

void UART_SendString(const char *str);

uint32_t UART_Received(uint8_t *buffer, uint32_t len, uint32_t timeout);

/**
 * @brief Transmit a single character over UART (USART1).
 * 
 * This function waits until the transmit data register (TDR) is empty,
 * then writes the character to the TDR, which sends it over the UART.
 * 
 * @param c The character to transmit.
 */
void UART_send_char(char c);

/**
 * @brief Receive a single character from UART (USART1).
 * 
 * This function waits until data is received and ready to be read
 * (RXNE = 1), then returns the received character from the RDR.
 * 
 * @return The received character.
 */
char UART_receive_char(void);

#endif
