#include "../include/time.h"

__attribute__((always_inline)) static inline uint64_t read_mtime(void)
{
    const uint64_t* ptr = MTIME_ADDR;
    return *ptr;
}

__attribute__((always_inline)) static inline void write_mtimecmp(uint64_t value)
{
    volatile uint64_t* ptr = MTIMECMP_ADDR;
    *ptr = value;
}