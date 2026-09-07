---
name: stm32f103zet6-bsp-setup
description: Use this skill when creating a new NuttX/openvela BSP (board support package) for the STM32F103ZET6 chip, or when scaffolding the defconfig, board.h pin definitions, or board_boot.c entry points for this board. Covers the 72 MHz clock tree (HSE 8 MHz + PLL x9), 64 KB SRAM at 0x20000000, and the standard board initialization entry points.
metadata:
  origin: contest2026_316_famous
---

# STM32F103ZET6 BSP Setup

Scaffold a minimal but complete NuttX BSP for the STM32F103ZET6
(Cortex-M3, 512 KB Flash, 64 KB SRAM, 72 MHz). Use this whenever the
project needs a new board directory or a clean board-level skeleton.

## When to Activate

- Creating a board under `boards/arm/stm32/<board>/` for STM32F103ZET6.
- Generating or repairing the NSH `defconfig`.
- Writing `board.h` (clock + pin definitions) or `board_boot.c` (entry points).
- Re-checking clock tree / memory layout after a porting change.

## Hardware Reference (STM32F103ZET6)

| Parameter | Value |
|-----------|-------|
| Core      | ARM Cortex-M3 (no FPU) |
| Flash     | 512 KB @ 0x08000000 |
| SRAM      | 64 KB @ 0x20000000 |
| Max SYSCLK| 72 MHz |
| Max APB1  | 36 MHz |
| Max APB2  | 72 MHz |

## Clock Tree (72 MHz)

```
HSE (8 MHz) -> PLL (x9) -> SYSCLK (72 MHz)
                            |
                       AHB  (72 MHz)
                       +-- APB2 (72 MHz) -> USART1, SPI1, TIM1, ADC1
                       +-- APB1 (36 MHz) -> USART2/3, TIM2-7, I2C1, RTC
```

Key `board.h` macros:

```c
#define STM32_BOARD_XTAL        8000000UL
#define STM32_CFGR_PLLSRC       RCC_CFGR_PLLSRC
#define STM32_CFGR_PLLXTPRE     0
#define STM32_CFGR_PLLMUL       RCC_CFGR_PLLMUL_CLKx9
#define STM32_PLL_FREQUENCY     (9 * STM32_BOARD_XTAL)
#define STM32_SYSCLK_SW         RCC_CFGR_SW_PLL
#define STM32_SYSCLK_FREQUENCY  STM32_PLL_FREQUENCY
#define STM32_RCC_CFGR_HPRE     RCC_CFGR_HPRE_SYSCLK
#define STM32_HCLK_FREQUENCY    STM32_PLL_FREQUENCY
#define STM32_RCC_CFGR_PPRE2    RCC_CFGR_PPRE2_HCLK
#define STM32_PCLK2_FREQUENCY   STM32_HCLK_FREQUENCY
#define STM32_RCC_CFGR_PPRE1    RCC_CFGR_PPRE1_HCLKd2
#define STM32_PCLK1_FREQUENCY   (STM32_HCLK_FREQUENCY / 2)
#define STM32_LSI_FREQUENCY     40000   /* IWDG clock source */
```

## Memory Layout (defconfig)

```ini
CONFIG_RAM_START=0x20000000
CONFIG_RAM_SIZE=65536
CONFIG_MM_REGIONS=1
```

## Board Entry Points

Two standard functions are required:

1. `void stm32_boardinitialize(void)` — early init, called after memory is
   mapped but before device init. Configure on-board GPIO, LEDs, buttons, and
   board-specific peripheral pins (chip select, etc.).

2. `int board_app_initialize(uintptr_t arg)` — application init, invoked via
   `boardctl(BOARDIOC_INIT)` because `CONFIG_NSH_ARCHINIT=y`. It returns the
   result of `stm32_bringup()`, which registers `/dev/*` drivers.

## Minimal defconfig Essentials

```ini
CONFIG_ARCH="arm"
CONFIG_ARCH_CHIP="stm32"
CONFIG_ARCH_CHIP_STM32F103ZE=y
CONFIG_STM32_STM32F10XX=y
CONFIG_ARCH_CORTEXM3=y
CONFIG_ARCH_NOFPU=y
CONFIG_ARCH_BOARD="contest2026_316_board"
CONFIG_STM32_USART1=y
CONFIG_USART1_SERIAL_CONSOLE=y
CONFIG_SYSTEM_NSH=y
CONFIG_NSH_ARCHINIT=y
```

## Pin Definitions (board.h)

Prefer the chip legacy pinmap (`hardware/stm32f103z_pinmap_legacy.h`) for
peripheral pins (USART/SPI/I2C/ADC/TIM) — do NOT redefine `GPIO_SPI1_SCK`,
`GPIO_I2C1_SCL`, `GPIO_ADC1_IN*`, etc. Only define board-specific pins
(LEDs, buttons, chip-select) in `board.h`. Example:

```c
#define GPIO_LED1   (GPIO_OUTPUT | GPIO_CNF_OUTPP | GPIO_MODE_50MHz | \
                     GPIO_OUTPUT_CLEAR | GPIO_PORTB | GPIO_PIN0)
#define GPIO_SPI1_CS (GPIO_OUTPUT | GPIO_CNF_OUTPP | GPIO_MODE_50MHz | \
                     GPIO_OUTPUT_SET | GPIO_PORTA | GPIO_PIN4)
```

## Build

```bash
./build.sh <board>:nsh -j8        # openvela wrapper
# or, on a NuttX checkout:
#   make distclean && ./tools/configure.sh <board>:nsh && make -j8
```

## Checklist

- [ ] `CONFIG_ARCH_CHIP_STM32F103ZE=y` and `CONFIG_STM32_STM32F10XX=y`
- [ ] 72 MHz clock macros consistent (PLL x9, APB1 /2)
- [ ] `STM32_LSI_FREQUENCY` defined if IWDG is used
- [ ] No pinmap macro redefinitions in `board.h`
- [ ] `stm32_boardinitialize()` + `board_app_initialize()` present
