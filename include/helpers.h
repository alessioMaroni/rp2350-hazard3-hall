#ifndef HELPERS_H
#define HELPERS_H

__attribute__((always_inline)) static inline void arch_asm_nop(void) 
{
#if (defined(__GNUC__) || defined(__clang__)) && !defined(__CPPCHECK__)
    __asm__ volatile("nop");
#endif
}

#endif
