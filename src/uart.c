#include "../include/uart.h"
#include "../include/helpers.h"

#include <stdint.h>

#define UART_TIMEOUT_CYCLES  1000000U

/**
 * @brief Release UART0 from reset
 */
__attribute__((always_inline)) static inline void uart_set_reset(void)
{
        // cppcheck-suppress misra-c2012-11.4
        RESETS->RESET |= RESETS_ALL_REQUIRED;

        for (volatile int i = 0; i < 100; i++) {
                arch_asm_nop();
        }

        // cppcheck-suppress misra-c2012-11.4
        RESETS->RESET &= ~RESETS_ALL_REQUIRED;
}

/**
 * @brief Wait until UART0 is ready (Polling su RESET_DONE)
 */
__attribute__((always_inline)) static inline int uart_reset_wait(void)
{
	uint32_t timeout = UART_TIMEOUT_CYCLES;

        while (((RESETS->RESET_DONE & RESETS_ALL_REQUIRED) != RESETS_ALL_REQUIRED) && (timeout > 0U))
    	{
        	timeout--;
        	arch_asm_nop();
    	}

	*SIO_SCRATCH1 = RESETS->RESET_DONE;

        return ((RESETS->RESET_DONE & RESETS_ALL_REQUIRED) == RESETS_ALL_REQUIRED) ? 0 : -1;
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

int uart_init(void)
{
	int ret;

        uart_set_reset();
	ret = uart_reset_wait();

	if (ret != 0) {
        	*SIO_SCRATCH0 = 0xDEAD0001U;
        	ret = -1; /* Timeout hardware */
    	} else {
        	uart_init_gpio();
        	uart_configure();
    	}

	return ret;
}

__attribute__((always_inline)) static inline void uart_wait_tx_free_space(void)
{
    while ((UART0->FR & UART_FR_TXFF_BIT) != 0U)
        {
                arch_asm_nop();
        }

}

void uart_write_byte(uint8_t byte)
{
    	uart_wait_tx_free_space();
        UART0->DR = (uint32_t)byte;
}
