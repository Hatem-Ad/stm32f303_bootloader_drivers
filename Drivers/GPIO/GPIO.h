#ifndef GPIO_H
#define GPIO_H



//GPIO Modes
#define GPIO_MODE_INPUT     0x0
#define GPIO_MODE_OUTPUT    0x1
#define GPIO_MODE_AF        0x2
#define GPIO_MODE_ANALOG    0x3

#define GPIO_OTYPE_PP       0x0 // Push-Pull
#define GPIO_OTYPE_OD       0x1 // Open-Drain


void GPIO_Init(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);
uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin_number);
void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin_number, uint8_t state);
void GPIO_TogglePin(GPIO_TypeDef *port, int8_t pin_number);


#endif
