/**
 * @file helpers.h
 * @brief Architecture-specific inline assembly helpers and safety assertion macros.
 *
 * Provides low-level primitives for RISC-V/ARM pipeline delays and bare-metal
 * assertion mechanisms for the RP2350 Hazard3 HAL.
 */

#ifndef HELPERS_H
#define HELPERS_H

#include "serial.h"

#include <stdint.h>

/**
 * @brief Executes a single NOP (No Operation) assembly instruction.
 *
 * Forces an explicit pipeline delay cycle on the target architecture.
 * Enclosed with static inline and compiler directives to guarantee inlining
 * while bypassing static analysis warnings (e.g., MISRA C:2012 Rule 17.3).
 *
 * @note Shielded against static analysis tools via __CPPCHECK__ guard.
 */
__attribute__((always_inline)) static inline void arch_asm_nop(void)
{
#if (defined(__GNUC__) || defined(__clang__)) && !defined(__CPPCHECK__)
	__asm__ volatile("nop");
#endif /* (defined(__GNUC__) || defined(__clang__)) && !defined(__CPPCHECK__) */
}

/**
 * @brief Helper macro for 32-bit register dereferencing.
 */
#define REG32(addr) (*((volatile uint32_t *)(uintptr_t)(addr)))

/**
 * @brief Bare-metal assertion macro for contract and state invariant checking.
 *
 * Evaluates the specified boolean condition. If the condition evaluates to false,
 * it writes a diagnostic fault code (0xDEADFFFFU) directly to the RP2350 SIO
 * Scratchpad 0 register (0xD0000000) and halts execution in an infinite NOP loop.
 *
 * Enforces NASA JPL "Power of 10" Rule 5 (Assertion Density) without requiring
 * standard C library support (libc) or dynamic allocation.
 *
 * @param[in] cond Boolean condition or hardware invariant expression to evaluate.
 */
#define ASSERT(cond) \
	do { \
		if (!(cond)) { \
			*SIO_SCRATCH0 = SIO_FAULT_ASSERT; \
			while (1) { \
				arch_asm_nop(); \
			} \
		} \
	} while (0)

#endif /* HELPERS_H */
