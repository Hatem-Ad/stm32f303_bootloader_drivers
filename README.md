# 🚀 STM32F303 Bootloader & Drivers – Baseline v1.0

## 📘 Overview

This project implements a custom UART bootloader and a full set of low-level drivers for the STM32F303VCT6 microcontroller (Cortex-M4 core).
It is developed as part of a professional embedded software framework for aeronautical-grade MCU bring-up, focusing on modularity, reliability, and transparency.

The bootloader allows:

Firmware updates via UART

Application jump to a user firmware located at 0x08004000

Watchdog protection and system safety checks

GPIO-based trigger for bootloader mode

SysTick timer for timing and delays

Structured driver architecture following layered embedded design

This version (v1.0) serves as the baseline reference implementation — clean, readable, and extendable for future versions (CRC, CAN, Ethernet, or secure boot).

---

## ✨ Highlights

- 🚀 **Custom Bootloader** — Handles firmware updates via UART, validates vectors, and safely jumps to the user application.
- 📡 **UART Communication** — Lightweight, register-level TX/RX driver used for firmware transfer and debug logs.
- ⚡ **GPIO Control** — Fast, direct register access for LED indicators and boot-trigger button management.
- 🔥 **FLASH Programming** — Reliable erase / write driver supporting application-area updates while preserving bootloader integrity.
- 🧩 **Structured Memory Map** — Clear separation between Bootloader (0x08000000 – 0x08003FFF) and Application (from 0x08004000).
- ⏱️ **SysTick Timing** — 1 ms system tick providing delays and timeouts across all modules.
- 🛡️ **Independent Watchdog (IWDG)** — Optional safety mechanism using the internal 40 kHz LSI clock.
- 🛠️ **Makefile-Based Build System** — Simple, IDE-independent compilation with arm-none-eabi-gcc and easy CI/CD integration.
- 🔬 **ST-Link / OpenOCD Support** — Full command-line debug and flashing capability under Linux or Windows environments.

---

## 🧩 System Architecture

| Step  | Description                                                      |
| ----- | ---------------------------------------------------------------- |
| **1** | Initializes system peripherals (**GPIO**, **UART**, **SysTick**) |
| **2** | Checks trigger pin → enter update mode or jump to application    |
| **3** | Receives new firmware via **UART**                               |
| **4** | Erases & programs **FLASH** in chunks                            |
| **5** | Verifies & jumps to user application at **0x08004000**           |

               │
               ▼
| Phase                      | Description                                                   |
| -------------------------- | ------------------------------------------------------------- |
| **User Application (APP)** | Located at **0x08004000**. Runs independently after jump.     |
| **Drivers**                | Uses shared drivers for **UART**, **GPIO**, **SysTick**, etc. |



## ⚙️ Project Directory Structure

- **stm32f303_bootloader_drivers/**

    *bootloader/* — Bootloader source 
      ├── Bootloader.c/h        # Bootloader core logic
      └── main.c                # Bootloader entry point

    *drivers/* — Bare-metal drivers (no HAL)
      ├── GPIO/                 # GPIO driver (init, read, toggle) 
      ├── UART/                 # UART driver (init, send, receive)
      ├── FLASH/                # Flash erase/write operations
      ├── RCC/                  # Reset & Clock Control helper (HSI, LSI)
      ├── WDG/                  # Independent Watchdog driver (IWDG)
      └── SysTick/              # SysTick timer driver (1ms tick)

    *linker/* 
      ├── Bootloader.ld/        # Bootloader memory mapping (16 KB)
      └── App.ld /              # Application memory mapping (rest of flash) 

    *startup/*
      ├── startup_stm32f303.s   # Startup vector table and Reset_Handler
      └── system_stm32f3xx.c    # SystemInit() and clock setup

    *lib/*
      └── CMSIS/
          └── Device/ST/STM32F3xx/Include/
              └── STM32F3xx.h   # MCU register and bitfield definitions

    *build*                     # Compiled outputs (.elf, .bin)

    *Makefile*                  # Build system configuration

    *README.md*                 # Project documentation (this file)

## 🧱 Memory Map

| Region          | Start Address | Size   | Description              |
| --------------- | ------------- | ------ | ------------------------ |
| **Bootloader**  | `0x08000000`  | 16 KB  | Bootloader firmware      |
| **Application** | `0x08004000`  | 240 KB | User firmware            |
| **RAM**         | `0x20000000`  | 40 KB  | SRAM                     |
| **Stack Top**   | `_estack`     | —      | Defined in linker script |

## 🧩 Bootloader Operation Sequence

1️⃣ System Reset / Power-On

    Stack pointer set

    Reset_Handler runs

.   data copied to RAM, .bss zeroed

2️⃣ SystemInit()

    Configures clock source (HSI 8 MHz baseline)

3️⃣ Bootloader_Init()

    Initializes GPIO, UART, SysTick

4️⃣ Bootloader_CheckForUpdate()

    Reads PA0 pin:

    LOW → stay in bootloader

    HIGH → jump to application

5️⃣ Bootloader_ReceiveFirmware()

    Erases app flash area

    Receives UART data in chunks (128 B)

    Writes to flash

    Confirms success

6️⃣ Bootloader_JumpToApp()

    Validates app vector table

    Sets MSP

    Relocates VTOR

    Jumps to user app Reset_Handler