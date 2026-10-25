/**
 * @file uart.h
 * @brief Memory-mapped peripheral definitions and register structures for RP2350 UART0.
 *
 * Provides physical base addresses, MMIO register structures, atomic bitmask offsets,
 * peripheral configuration constants, and public API function declarations for UART0.
 */

#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "./serial.h"

/**
 * @brief Subsystem Reset Control Register Layout (RESETS).
 */
typedef struct {
	volatile uint32_t RESET;      /**< 0x00: Reset control register */
	volatile uint32_t WDSEL;      /**< 0x04: Watchdog reset select */
	volatile uint32_t RESET_DONE; /**< 0x08: Reset done status register */
} RESETS_Regs_t;

/**
 * @brief ARM PrimeCell UART (PL011) Register Layout.
 */
typedef struct {
	volatile uint32_t DR;        /**< 0x00: Data Register */
	volatile uint32_t RSR;       /**< 0x04: Receive Status / Error Clear Register */
	uint32_t reserved0[4];       /**< 0x08 - 0x14: Reserved unmapped space */
	volatile uint32_t FR;        /**< 0x18: Flag Register (TXFF, RXFE, BUSY) */
	uint32_t reserved1;          /**< 0x1C: Reserved unmapped space */
	volatile uint32_t ILPR;      /**< 0x20: IrDA Low Power Counter Register */
	volatile uint32_t IBRD;      /**< 0x24: Integer Baud Rate Divisor Register */
	volatile uint32_t FBRD;      /**< 0x28: Fractional Baud Rate Divisor Register */
	volatile uint32_t LCR_H;     /**< 0x2C: Line Control Register */
	volatile uint32_t CR;        /**< 0x30: Control Register */
	volatile uint32_t IFLS;      /**< 0x34: Interrupt FIFO Level Select Register */
	volatile uint32_t IMSC;      /**< 0x38: Interrupt Mask Set/Clear Register */
	volatile uint32_t RIS;       /**< 0x3C: Raw Interrupt Status Register */
	volatile uint32_t MIS;       /**< 0x40: Masked Interrupt Status Register */
	volatile uint32_t ICR;       /**< 0x44: Interrupt Clear Register */
	volatile uint32_t DMACR;     /**< 0x48: DMA Control Register */
} UART_Regs_t;

/**
 * @brief General Purpose Input/Output Bank 0 Control Layout (IO_BANK0).
 */
typedef struct {
	struct {
		volatile uint32_t STATUS; /**< Pin status register */
		volatile uint32_t CTRL;   /**< Pin control and function selection register */
	} GPIO[30];
} IO_BANK0_Regs_t;

/**
 * @brief Pad Control Bank 0 Register Layout (PADS_BANK0).
 */
typedef struct {
	volatile uint32_t VOLTAGE_SELECT; /**< 0x00: Voltage select register */
	volatile uint32_t PAD[30];        /**< Pad electrical configuration registers */
} PADS_BANK0_Regs_t;

/**
 * @name Peripheral Base Addresses
 * @{
 */
#define RESETS_BASE_ADDR     0x40028000UL /**< RESETS peripheral base address */
#define IO_BANK0_BASE_ADDR   0x40030000UL /**< IO_BANK0 peripheral base address */
#define PADS_BANK0_BASE_ADDR 0x40040000UL /**< PADS_BANK0 peripheral base address */
#define UART0_BASE_ADDR      0x40034000UL /**< UART0 peripheral base address */
/** @} */

/**
 * @name Atomic Bit Manipulation Offsets
 * @{
 */
#define ATOMIC_XOR_OFFSET    0x1000U /**< Atomic XOR alias offset */
#define ATOMIC_SET_OFFSET    0x2000U /**< Atomic SET alias offset */
#define ATOMIC_CLR_OFFSET    0x3000U /**< Atomic CLR (clear) alias offset */
/** @} */

/**
 * @name Peripheral Access Instances
 * @{
 */
#define RESETS     ((RESETS_Regs_t *)(uintptr_t)RESETS_BASE_ADDR)
#define RESETS_SET ((RESETS_Regs_t *)(uintptr_t)(RESETS_BASE_ADDR | ATOMIC_SET_OFFSET))
#define RESETS_CLR ((RESETS_Regs_t *)(uintptr_t)(RESETS_BASE_ADDR | ATOMIC_CLR_OFFSET))
#define UART0      ((UART_Regs_t *)(uintptr_t)UART0_BASE_ADDR)
#define IO_BANK0   ((IO_BANK0_Regs_t *)(uintptr_t)IO_BANK0_BASE_ADDR)
#define PADS_BANK0 ((PADS_BANK0_Regs_t *)(uintptr_t)PADS_BANK0_BASE_ADDR)
/** @} */

/**
 * @name UART Configuration Constants (115200 Baud @ 12 MHz clk_peri)
 * @{
 */
#define UART_IBAUD 6U                                  /**< Integer divisor part */
#define UART_FBAUD 33U                                 /**< Fractional divisor part */
#define UART_8N1   ((uint32_t)3U << 5U)                /**< 8 data bits, no parity, 1 stop bit */
#define UART_FIFO  ((uint32_t)1U << 4U)                /**< Enable hardware FIFOs */
#define UART_ENABLE (((uint32_t)1U << 9U) | \
		     ((uint32_t)1U << 8U) | \
		     ((uint32_t)1U << 0U))             /**< Control bitmask: RXE | TXE | UARTEN */
/** @} */

/**
 * @name Subsystem Reset and GPIO Multiplexing Masks
 * @{
 */
#define RESETS_RESET_UART0_BIT ((uint32_t)1U << 22U)  /**< UART0 reset bit position */
#define RESETS_IO_BANK0_BIT    ((uint32_t)1U << 6U)   /**< IO_BANK0 reset bit position */
#define RESETS_PADS_BANK0_BIT   ((uint32_t)1U << 9U)   /**< PADS_BANK0 reset bit position */
#define GPIO_FUNC_UART         2U                      /**< GPIO multiplexer function 2 (UART) */

#define PAD_TX_CONFIG 0x04U                            /**< Pad TX drive strength and slew rate */
#define PAD_RX_CONFIG 0x40U                            /**< Pad RX input enable configuration */

#define UART_FR_TXFF_BIT ((uint32_t)1U << 5U)          /**< Transmit FIFO full status bit */
#define UART_FR_RXFE_BIT ((uint32_t)1U << 4U)          /**< Receive FIFO empty status bit */

#define RESETS_UART0_BIT    RESETS_RESET_UART0_BIT     /**< Alias for UART0 reset bit */
#define RESETS_ALL_REQUIRED 0x00400240U                /**< Combined reset mask (UART0, IO_BANK0, PADS_BANK0) */
/** @} */

/**
 * @brief Helper macro for 32-bit register dereferencing.
 */
#define REG32(addr) (*((volatile uint32_t *)(uintptr_t)(addr)))

__attribute__((always_inline)) static inline void uart_set_reset(void);
__attribute__((always_inline)) static inline int uart_reset_wait(void);
__attribute__((always_inline)) static inline void uart_init_gpio(void);
__attribute__((always_inline)) static inline void uart_configure(void);

/**
 * @brief Initializes the UART0 hardware module and associated GPIO lines.
 *
 * Performs hardware reset of UART0, IO_BANK0, and PADS_BANK0, waits for reset completion,
 * configures GPIO0 (TX) and GPIO1 (RX), and sets the line control for 8N1 @ 115200 Baud.
 *
 * @return 0 on successful initialization, -1 on hardware timeout.
 */
int uart_init(void);

__attribute__((always_inline)) static inline void uart_wait_tx_free_space(void);

/**
 * @brief Transmits a single byte over UART0 TX.
 *
 * Blocks until space is available in the transmit FIFO (TXFF flag cleared),
 * then writes the payload byte to the UART Data Register (UARTDR).
 *
 * @param[in] byte The 8-bit data payload to transmit.
 */
void uart_write_byte(uint8_t byte);

#endif /* UART_H */
