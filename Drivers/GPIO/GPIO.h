#ifndef GPIO_H
#define GPIO_H

void GPIO_Init(void);
uint8_t GPIO_ReadPin(uint8_t pin_number);
void GPIO_WritePin(uint8_t pin_number, uint8_t state);
void GPIO_TogglePin(uint8_t pin_number);

#endif
