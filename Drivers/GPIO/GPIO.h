#ifndef GPIO_H
#define GPIO_H

//GPIO Modes
typedef enum{
    GPIO_MODE_INPUT  = 0x0,
    GPIO_MODE_OUTPUT = 0x1,
    GPIO_MODE_AF     = 0x2,
    GPIO_MODE_ANALOG = 0x3
} GPIO_mode_t;


typedef enum {
    GPIO_OTYPE_PP = 0x0, // Push-Pull
    GPIO_OTYPE_OD = 0x1  // Open-Drain
} GPIO_otype_t;

typedef enum {
    GPIO_SPEED_LOW    = 0,
    GPIO_SPEED_MEDIUM = 1,
    GPIO_SPEED_HIGH   = 2
} GPIO_speed_t;

typedef enum {
    GPIO_NPULL    = 0,
    GPIO_PULLUP   = 1,
    GPIO_PULLDOWN = 2
} GPIO_pull_t;


void GPIO_Init(GPIO_TypeDef    *port, 
               uint8_t          pin, 
               GPIO_mode_t      mode,
               GPIO_otype_t     otype,
               GPIO_speed_t     speed,
               GPIO_pull_t      pull);

void GPIO_Write(GPIO_TypeDef   *port, 
                uint8_t         pin, 
                uint8_t         state);

void GPIO_Toggle(GPIO_TypeDef  *port, 
                 uint8_t        pin);

void GPIO_Set_AF(GPIO_TypeDef  *port, 
                 uint8_t        pin,
                 uint8_t        af);

uint8_t GPIO_Read(GPIO_TypeDef *port, 
                  uint8_t       pin);

#endif
