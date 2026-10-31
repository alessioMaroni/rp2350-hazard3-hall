/**
 * @file rp2350_hal.h
 * @brief Master header file for the RP2350 Hazard3 Hardware Abstraction Layer (HAL).
 *
 * Serves as the primary entry point for the C library and Rust FFI bindings.
 * Aggregates peripheral driver interfaces including UART, GPIO, and SIO diagnostics
 * under C++ extern guards for cross-language compatibility.
 */

#ifndef RP2350_HAL_H
#define RP2350_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "uart.h"

#ifdef __cplusplus
}
#endif

#endif /* RP2350_HAL_H */
