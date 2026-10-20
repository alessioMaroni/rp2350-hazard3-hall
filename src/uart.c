#include "../include/uart.h"

#include <stdint.h>

__attribute__((always_inline)) static inline void uart_set_reset(void)
{
	// cppcheck-suppress misra-c2012-11.4 
        RESETS_SET->RESET = RESETS_RESET_UART0_BIT;

	// cppcheck-suppress misra-c2012-11.4
        RESETS_CLR->RESET = RESETS_RESET_UART0_BIT;
}

__attribute__((always_inline)) inline void uart_init(void)
{
        uart_set_reset();
}
