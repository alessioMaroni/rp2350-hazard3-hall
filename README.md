# RP2350 Hazard3 RISC-V HAL

[![Datasheet](https://img.shields.io/badge/Datasheet-RP2350%20PDF-C51A4A?style=for-the-badge&logo=raspberrypi&logoColor=white)](https://pip-assets.raspberrypi.com/categories/1214-rp2350/documents/RP-008373-DS-3-rp2350-datasheet.pdf)
[![MISRA C](https://img.shields.io/badge/Standard-MISRA%20C%3A2012/2025-800020?style=for-the-badge)](https://misra.org.uk)
[![License](https://img.shields.io/badge/License-Apache%202.0%20%2F%20MIT-yellow?style=for-the-badge)](./LICENSE-APACHE)

A production-grade **RP2350 Hazard3 RISC-V Hardware Abstraction Layer (HAL)**.  
Designed for **Safety-Critical Systems** with strict compliance to **MISRA C:2012 / MISRA C:2023** and **The Power of Ten** coding standards.

## Key Features

* **Dual Compilance Enforcement**
    * **MISRA C:2012 / 2025:** Mandatory compliance for safety-critical C software development.
    * **NASA JPL "Power of Ten":** Enforcement of strict bounds, minimal function length, constrained preprocessor usage, and assertion density.
* **Defensive Hardware Access:** Volatile type-safety wrappers for register access preventing unexpected compiler optimizations or undefined behavior.

## Current Developing Status

* [⚠] [**UART**](./include/uart.h)
    - [✔] output
    - [✖] input