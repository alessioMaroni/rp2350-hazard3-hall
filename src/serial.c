#include "serial.h"

__attribute__((always_inline)) inline void uart_write_byte(uint8_t byte)
{
    while ((*UART0_FR_PTR & UART_FR_TXFF) != 0);
    *UART0_DR_PTR = (uint32_t)byte;
}