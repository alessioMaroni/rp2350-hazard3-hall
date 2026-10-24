#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

/* RESETS Peripheral */
typedef struct {
    volatile uint32_t RESET;
    volatile uint32_t WDSEL;
    volatile uint32_t RESET_DONE;
} RESETS_Regs_t;

/* UART Peripheral */
typedef struct {
    volatile uint32_t DR;        /* 0x00 */
    volatile uint32_t RSR;       /* 0x04 */
    uint32_t reserved0[4];       /* 0x08 - 0x14 Unmapped */
    volatile uint32_t FR;        /* 0x18 */
    uint32_t reserved1;          /* 0x1C     Unmapped*/
    volatile uint32_t ILPR;      /* 0x20 */
    volatile uint32_t IBRD;      /* 0x24 */
    volatile uint32_t FBRD;      /* 0x28 */
    volatile uint32_t LCR_H;     /* 0x2C */
    volatile uint32_t CR;        /* 0x30 */
    volatile uint32_t IFLS;      /* 0x34 */
    volatile uint32_t IMSC;      /* 0x38 */
    volatile uint32_t RIS;       /* 0x3C */
    volatile uint32_t MIS;       /* 0x40 */
    volatile uint32_t ICR;       /* 0x44 */
    volatile uint32_t DMACR;     /* 0x48 */
} UART_Regs_t;

/* IO_BANK0 Peripheral (GPIO Control) */
typedef struct {
    struct {
        volatile uint32_t STATUS; /* Offset 0x00, 0x08, 0x10... */
        volatile uint32_t CTRL;   /* Offset 0x04, 0x0C, 0x14... */
    } GPIO[30];
} IO_BANK0_Regs_t;

/* PADS_BANK0 Peripheral */
typedef struct {
    volatile uint32_t VOLTAGE_SELECT; /* Offset 0x00 */
    volatile uint32_t PAD[30];        /* Offset 0x04, 0x08, 0x0C... */
} PADS_BANK0_Regs_t;

#define RESETS_BASE_ADDR        0x40028000UL
#define IO_BANK0_BASE_ADDR      0x40030000UL
#define PADS_BANK0_BASE_ADDR    0x40040000UL
#define UART0_BASE_ADDR         0x40034000UL

/* Atomic Offsets */
#define ATOMIC_XOR_OFFSET       0x1000U
#define ATOMIC_SET_OFFSET       0x2000U
#define ATOMIC_CLR_OFFSET       0x3000U

#define RESETS          ((RESETS_Regs_t *)(uintptr_t)RESETS_BASE_ADDR)
#define RESETS_SET      ((RESETS_Regs_t *)(uintptr_t)(RESETS_BASE_ADDR | ATOMIC_SET_OFFSET))
#define RESETS_CLR      ((RESETS_Regs_t *)(uintptr_t)(RESETS_BASE_ADDR | ATOMIC_CLR_OFFSET))
#define UART0           ((UART_Regs_t *)(uintptr_t)UART0_BASE_ADDR)
#define IO_BANK0        ((IO_BANK0_Regs_t *)(uintptr_t)IO_BANK0_BASE_ADDR)
#define PADS_BANK0      ((PADS_BANK0_Regs_t *)(uintptr_t)PADS_BANK0_BASE_ADDR)

#define UART_IBAUD               6U
#define UART_FBAUD               33U
#define UART_8N1                 ((uint32_t)3U << 5U)
#define UART_FIFO                ((uint32_t)1U << 4U)
#define UART_ENABLE              (((uint32_t)1U << 9U) | \
                                  ((uint32_t)1U << 8U) | \
                                  ((uint32_t)1U << 0U))

#define RESETS_RESET_UART0_BIT   ((uint32_t)1U << 22U)
#define RESETS_IO_BANK0_BIT      ((uint32_t)1U << 6U)
#define RESETS_PADS_BANK0_BIT    ((uint32_t)1U << 9U)
#define GPIO_FUNC_UART           2U

#define PAD_TX_CONFIG    0x04U
#define PAD_RX_CONFIG     0x40U

#define UART_FR_TXFF_BIT    ((uint32_t)1U << 5U)
#define UART_FR_RXFE_BIT    ((uint32_t)1U << 4U)

#define RESETS_UART0_BIT         RESETS_RESET_UART0_BIT
#define RESETS_ALL_REQUIRED      0x00400240U

#define SIO_SCRATCH0 ((volatile uint32_t *)0xd0000000U)
#define SIO_SCRATCH1 ((volatile uint32_t *)0xd0000004U)

/* TODO: Consider to move this macro helper */
#define REG32(addr) (*((volatile uint32_t *)(uintptr_t)(addr)))

__attribute__((always_inline)) static inline void uart_set_reset(void);
__attribute__((always_inline)) static inline int uart_reset_wait(void);
__attribute__((always_inline)) static inline void uart_init_gpio(void);
__attribute__((always_inline)) static inline void uart_configure(void);

int uart_init(void);

__attribute__((always_inline)) static inline void uart_wait_tx_free_space(void);
void uart_write_byte(uint8_t byte);

#endif
