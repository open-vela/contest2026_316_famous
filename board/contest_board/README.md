# STM32F103ZET6 Board Support Package (BSP)

## Overview

This directory contains the Board Support Package for STM32F103ZET6 development board, adapted for openvela/NuttX RTOS.

## Hardware Specifications

| Parameter | Value |
|-----------|-------|
| MCU | STM32F103ZET6 |
| Core | ARM Cortex-M3 |
| Clock | 72 MHz (HSE 8MHz + PLL x9) |
| Flash | 512 KB |
| SRAM | 64 KB |
| GPIO | 80 pins |
| USART | 3x (USART1, USART2, USART3) |
| SPI | 2x |
| I2C | 2x |
| USB | 1x |
| CAN | 1x |
| ADC | 3x (12-bit) |
| DAC | 2x |

## Console Configuration

- **USART1**: PA9 (TX), PA10 (RX)
- **Baud Rate**: 115200
- **Data Bits**: 8
- **Stop Bits**: 1
- **Parity**: None

## LED Configuration

| LED | Pin | Description |
|-----|-----|-------------|
| LED1 | PB0 | Green LED |
| LED2 | PB1 | Yellow LED |
| LED3 | PB5 | Red LED |

## Button Configuration

| Button | Pin | Description |
|--------|-----|-------------|
| USER | PA0 | User button (active low) |

## Building

```bash
# From openvela workspace root
./build.sh contest2026_316_board:nsh -j8
```

## Flashing

Use ST-Link or J-Link to flash the generated `nuttx.hex` or `nuttx.bin` file.

### Using ST-Link CLI:
```bash
st-flash write nuttx.bin 0x08000000
```

### Using OpenOCD:
```bash
openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg \
  -c "program nuttx.elf verify reset exit"
```

## Serial Connection

Connect a USB-UART adapter to:
- TX (PA9) → RX on adapter
- RX (PA10) → TX on adapter
- GND → GND

Open serial terminal at 115200 baud, 8N1.

## NSH Commands

After successful boot, you should see the `nsh>` prompt. Available commands:

```
nsh> help
nsh> uname -a
nsh> ps
nsh> free
nsh> ls /dev
```

## Directory Structure

```
contest_board/
├── CMakeLists.txt      # Top-level CMake file
├── Kconfig             # Board Kconfig
├── README.md           # This file
├── configs/
│   └── nsh/
│       └── defconfig   # NSH configuration
├── include/
│   └── board.h         # Board header (clock, pins)
└── src/
    ├── CMakeLists.txt     # Source CMake file
    ├── board_boot.c       # Board entry points (boardinitialize/app_initialize)
    ├── stm32_bringup.c    # Registers /dev/userleds, /dev/buttons
    ├── stm32_gpio.c       # GPIO/LED/button pin configuration
    ├── stm32_spi.c        # SPI1 pin configuration
    ├── stm32_i2c.c        # I2C1 pin configuration
    ├── stm32_userleds.c   # Standard user LED driver
    └── stm32_buttons.c    # Standard button driver
```

## References

- [STM32F103ZET6 Datasheet](https://www.st.com/resource/en/datasheet/stm32f103ze.pdf)
- [STM32F103xx Reference Manual](https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [NuttX STM32 Documentation](https://nuttx.apache.org/docs/latest/platforms/arm/stm32/index.html)
