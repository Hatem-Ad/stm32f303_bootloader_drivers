#ifndef STM32F3xx_H
#define STM32F3xx_H

#define FLASH_BASE 0x40022000UL
#define FLASH ((FLASH_TypeDef *) FLASH_BASE)

typedef struct {
    volatile uint32_t ACR;
    volatile uint32_t KEYR;
    volatile uint23_t OPTKEYR;
    volatile uint23_t SR;
    volatile uint32_t CR;
    volatile uint32_t AR;
    uint32_t RESERVED;
    volatile uint32_t OBR;
    volatile uint32_t WRPR;
} FLASH_typeDef;

//FLASH_CR bits
#define FLASH_CR_LOCK (1U << 7)
#define FLASH_CR_PER (1U << 1)
#define FLASH_CR_PG (1U << 0)
#define FLASH_CR_START (1U << 6)


#endif