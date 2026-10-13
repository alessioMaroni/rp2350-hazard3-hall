#include "../include/serial.h"

__attribute__((always_inline)) static inline void uart_write_byte(uint8_t byte)
{
    while (UART0_FR & UART_FR_TXFF);
    UART0_FIFO_REG = (uint32_t)byte;
}

