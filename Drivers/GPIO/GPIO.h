#ifndef GPIO_H
#define GPIO_H

void GPIO_Init(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);
uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin_number);
void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin_number, uint8_t state);
void GPIO_TogglePin(GPIO_TypeDef *port, int8_t pin_number);

#endif
