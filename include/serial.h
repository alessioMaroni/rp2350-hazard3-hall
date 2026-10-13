#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stddef.h>

#define UART0_BASE 0x40070000
#define UART1_BASE 0x40078000

#define UART0_DR (*(volatile uint32_t *)(UART0_BASE + 0x000))
#define UART0_FR (*(volatile uint32_t *)(UART0_BASE + 0x018))

#define UART_FR_TXFF (1u << 5)

__attribute__((always_inline)) static inline void uart_write_byte(uint8_t byte);

#endif
