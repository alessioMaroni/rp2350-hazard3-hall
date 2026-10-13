#include "../include/time.h"

uint64_t read_mtime(void)
{
    return *MTIME_PTR;
}

void write_mtimecmp(uint64_t value)
{
    *MTIMECMP_PTR = value;
}