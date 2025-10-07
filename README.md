# 🚀 STM32F303 Bootloader & Drivers

A clean, modular, and register-level embedded project for the STM32F303 Discovery board — featuring a custom bootloader, GPIO/UART drivers, and support for user applications. Designed for performance, control, and flexibility in bare-metal development.

---

## ✨ Highlights

- 🏁 **Custom Bootloader** — Jump to user app, startup routine, vector handling
- 📡 **UART Driver** — Minimal implementation with TX/RX support
- ⚡ **GPIO Driver** — Fast pin-mode config and digital I/O handling
- 🧠 **FLASH Memory Management** — Planned: in-place firmware updates
- 🧩 **Memory Map Separation** — App and bootloader coexist in flash
- 🛠️ **Makefile-based** — No IDE lock-in, easy CI integration
- 🧪 **ST-Link + OpenOCD** — Debug and flash from CLI

---

## 📁 Project Structure


- **stm32f303_bootloader_drivers/**

    **bootloader/** — Bootloader source (starts at 0x08000000)

        Bootloader.c/h — Bootloader jump and validity checks

        startup_stm32f303.s* — Reset handler and vector table

        Bootloader.ld — Bootloader linker script

        App.ld — Application linker script

    *drivers/* — Bare-metal drivers (no HAL)

        GPIO.c/h — GPIO input/output/toggle

        UART.c/h — UART init, send/receive

        FLASH.c/h — Internal FLASH write/erase

    *user_app/* — Sample user application (starts at 0x08004000)

        main.c — Blink LED + send UART message

        linker.ld — App-specific linker script

    *include/* — Shared headers (e.g., STM32F3xx.h)

    *Makefile* — Builds bootloader or user app

    *README.md* — This file

