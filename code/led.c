#include <stdint.h>

// registers for GPIOB
#define GPIOB_BASE 0x50000400
#define MODER   *(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define OTYPER  *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define OSPEEDR *(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define PUPDR   *(volatile uint32_t *)(GPIOB_BASE + 0x0C)
#define IDR     *(volatile uint32_t *)(GPIOB_BASE + 0x10)
#define ODR     *(volatile uint32_t *)(GPIOB_BASE + 0x14)
#define BSRR    *(volatile uint32_t *)(GPIOB_BASE + 0x18)
#define LCKR    *(volatile uint32_t *)(GPIOB_BASE + 0x1C)
#define AFRL    *(volatile uint32_t *)(GPIOB_BASE + 0x20)
#define AFRH    *(volatile uint32_t *)(GPIOB_BASE + 0x24)
#define BRR     *(volatile uint32_t *)(GPIOB_BASE + 0x28)

// GPIO clock enable register
#define RCC_BASE 0x40021000
#define IOPENR  *(volatile uint32_t *)(RCC_BASE + 0x2C)

int main() {
    // setting 
    IOPENR = 0x00000002;
    MODER  = 0x55555555;
    ODR    = 0x000000FF;
    while(1) {
        for (int i = 0; i < 8; i++) {
            ODR = 1 << i;
            for (int j = 0; j < 50000; j++) { }
        }
    }
}
