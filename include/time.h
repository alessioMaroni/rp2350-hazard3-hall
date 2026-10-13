#ifndef TIME_H
#define TIME_H

#include <stdint.h>

#define TIME_BASE_ADDR 0x0200_0000
#define MTIMECMP_ADDR (*(volatile uint64_t *)(TIME_BASE_ADDR + 0x4000))
#define MTIME_ADDR (*(volatile uint64_t *)(TIME_BASE_ADDR + 0xBFF8))

__attribute__((always_inline)) static inline uint64_t read_mtime(void);

__attribute__((always_inline)) static inline void write_mtimecmp(uint64_t value);

#endif