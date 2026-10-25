/**
 * @file serial.h
 * @brief Memory-mapped register definitions and diagnostic codes for RP2350 SIO.
 *
 * Contains memory base addresses, atomic offsets, hardware register structures,
 * and diagnostic scratchpad magic numbers for the RP2350 Hazard3 HAL.
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

/**
 * @name Single-Cycle I/O (SIO) Peripheral Addresses
 * @{
 */
#define SIO_BASE_ADDR        0xD0000000UL                          /**< SIO base memory address */
#define SIO_SCRATCH0_ADDR    ((uint32_t)SIO_BASE_ADDR + 0x000U)    /**< Scratchpad register 0 physical address */
#define SIO_SCRATCH1_ADDR    ((uint32_t)SIO_BASE_ADDR + 0x004U)    /**< Scratchpad register 1 physical address */
/** @} */

/**
 * @name SIO Scratchpad Register Access Pointers
 * @{
 */
#define SIO_SCRATCH0         ((volatile uint32_t *)SIO_SCRATCH0_ADDR)  /**< Pointer to SIO Scratchpad 0 (Fault logging) */
#define SIO_SCRATCH1         ((volatile uint32_t *)SIO_SCRATCH1_ADDR)  /**< Pointer to SIO Scratchpad 1 (Status logging) */
/** @} */

/**
 * @name Diagnostic Fault Magic Numbers
 * @{
 */
#define SIO_FAULT_TIMEOUT    0xDEAD0001U  /**< Hardware reset or peripheral polling timeout fault */
#define SIO_FAULT_ASSERT     0xDEADFFFFU  /**< Pre/post-condition assertion failure fault */
/** @} */

#endif /* SERIAL_H */
