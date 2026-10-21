#include "../include/uart.h"

#include <stdint.h>

/**
 * @brief Release UART0 from reset
 */
__attribute__((always_inline)) static inline void uart_set_reset(void)
{
        // cppcheck-suppress misra-c2012-11.4
        RESETS_SET->RESET = RESETS_RESET_UART0_BIT;

        // cppcheck-suppress misra-c2012-11.4
        RESETS_CLR->RESET = RESETS_RESET_UART0_BIT;
}

/**
 * @brief Wait until UART0 is ready (Polling su RESET_DONE)
 */
__attribute__((always_inline)) static inline void uart_reset_wait(void)
{
        while ((RESETS->RESET_DONE & RESETS_RESET_UART0_BIT) == 0U)
	{

	}
}

__attribute__((always_inline)) static inline void uart_init_gpio(void)
{
        // cppcheck-suppress misra-c2012-11.4
        IO_BANK0->GPIO[0].CTRL = GPIO_FUNC_UART;
        // cppcheck-suppress misra-c2012-11.4
        IO_BANK0->GPIO[1].CTRL = GPIO_FUNC_UART;

        // cppcheck-suppress misra-c2012-11.4
        PADS_BANK0->PAD[0] = PAD_TX_CONFIG;
        // cppcheck-suppress misra-c2012-11.4
        PADS_BANK0->PAD[1] = PAD_RX_CONFIG;
}


__attribute__((always_inline)) static inline void uart_configure(void)
{
        // cppcheck-suppress misra-c2012-11.4
        UART0->CR = 0U;

        // cppcheck-suppress misra-c2012-11.4
        UART0->IBRD = UART_IBAUD;
        // cppcheck-suppress misra-c2012-11.4
        UART0->FBRD = UART_FBAUD;

        // cppcheck-suppress misra-c2012-11.4
        UART0->LCR_H = UART_8N1 | UART_FIFO;

        // cppcheck-suppress misra-c2012-11.4
        UART0->CR = UART_ENABLE;
}

void uart_init(void)
{
        uart_set_reset();
        uart_reset_wait();
        uart_init_gpio();
        uart_configure();
}
