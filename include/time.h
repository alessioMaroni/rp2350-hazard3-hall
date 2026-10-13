#ifndef TIME_H
#define TIME_H

#include <stdint.h>

#define TIME_BASE_ADDR  0x02000000U
#define MTIMECMP_PTR ((volatile uint64_t *)(TIME_BASE_ADDR + 0x4000U))
#define MTIME_PTR    ((volatile uint64_t *)(TIME_BASE_ADDR + 0xBFF8U))

uint64_t read_mtime(void);
void write_mtimecmp(uint64_t value);

#endif
