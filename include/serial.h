#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stddef.h>

#define UART0_BASE 0x40070000U
#define UART1_BASE 0x40078000U

#define UART0_DR_PTR ((volatile uint32_t *)(UART0_BASE + 0x000U))
#define UART0_FR_PTR ((volatile uint32_t *)(UART0_BASE + 0x018U))

#define UART_FR_TXFF (1u << 5)

void uart_write_byte(uint8_t byte);

#endif