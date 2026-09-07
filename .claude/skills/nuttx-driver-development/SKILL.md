---
name: nuttx-driver-development
description: Use this skill when adding or porting a NuttX device driver on STM32 (or other NuttX architectures). Covers the lower-half / upper-half model, the *_initialize() / *_register() pattern, Kconfig options, and wiring sources into CMakeLists.txt, with a reference table of common STM32 driver entry points.
metadata:
  origin: contest2026_316_famous
---

# NuttX Driver Development

Develop and register NuttX device drivers using the standard lower-half /
upper-half split. Use this skill when the project needs a new `/dev/*` node
for a peripheral (SPI, I2C, ADC, PWM, RTC, watchdog, etc.).

## When to Activate

- Adding a new peripheral driver or `/dev/*` node.
- Porting a driver to a new board or enabling it in Kconfig/defconfig.
- Debugging "Failed to register X" or "Failed to get X lower half" errors.

## Driver Model

- **Lower-half**: the arch/chip-specific driver. Its `*_initialize()` function
  returns a lower-half handle (e.g. `struct spi_dev_s *`).
- **Upper-half**: the generic framework. Its `*_register(path, lower)` binds
  the lower half and creates the `/dev/` node.

```
app -> /dev/pwm0 -> pwm_register() -> stm32_pwminitialize(1) -> TIM1
       (upper-half)                    (lower-half)
```

## Common STM32 Entry Points

| Peripheral | Lower-half initialize | Register | Dev path |
|------------|----------------------|----------|----------|
| SPI        | `stm32_spibus_initialize(int bus)` | (bind to upper driver) | — |
| I2C        | `stm32_i2cbus_initialize(int port)` | `i2c_register(i2c, bus)` | `/dev/i2cN` |
| ADC        | `stm32_adcinitialize(int intf, const uint8_t *chanlist, int n)` | `adc_register(path, adc)` | `/dev/adc0` |
| PWM        | `stm32_pwminitialize(int timer)` | `pwm_register(path, pwm)` | `/dev/pwm0` |
| RTC        | `stm32_rtc_lowerhalf()` | `rtc_initialize(minor, lower)` | `/dev/rtc0` |
| Watchdog   | `stm32_iwdginitialize(path, lsifreq)` | (self-registers) | `/dev/watchdog0` |

Board code must supply board-specific hooks for SPI:
`stm32_spiNselect()` and `stm32_spiNstatus()` (the common driver handles
SCK/MISO/MOSI and setfrequency/setmode/setbits itself).

## Kconfig Options

Add the peripheral config to the board `defconfig` (not hand-edit Kconfig
unless adding a new option). Typical entries:

```ini
CONFIG_SPI=y
CONFIG_STM32_SPI1=y
CONFIG_I2C=y
CONFIG_I2C_DRIVER=y
CONFIG_STM32_I2C1=y
CONFIG_ADC=y
CONFIG_STM32_ADC1=y
CONFIG_PWM=y
CONFIG_STM32_TIM1=y
CONFIG_STM32_TIM1_PWM=y
CONFIG_STM32_TIM1_CH1OUT=y   # route CH1 to PA8
CONFIG_RTC=y
CONFIG_RTC_DRIVER=y
CONFIG_WATCHDOG=y
CONFIG_STM32_IWDG=y
```

## CMakeLists.txt Wiring

Add the board's driver source files to the board target:

```cmake
target_sources(board PRIVATE
  board_boot.c
  stm32_bringup.c
  stm32_spi.c
  stm32_i2c.c
  stm32_adc.c
  stm32_pwm.c
)
```

## Bring-up Pattern

In `stm32_bringup.c`, guard each init with the matching `CONFIG_*` and log
failures with `syslog(LOG_ERR, ...)`. Use a `static bool initialized` guard
for idempotent setup. Example (I2C):

```c
#ifdef CONFIG_I2C_DRIVER
  struct i2c_master_s *i2c = stm32_i2cbus_initialize(1);
  if (i2c == NULL) {
    syslog(LOG_ERR, "ERROR: Failed to get I2C1 interface\n");
  } else {
    int ret = i2c_register(i2c, 1);
    if (ret < 0) stm32_i2cbus_uninitialize(i2c);
  }
#endif
```

## Testing

- Build: `./build.sh <board>:nsh -j8`.
- Boot and run `nsh> ls /dev` to confirm the node exists.
- Exercise the device (e.g. read `/dev/adc0`, set `/dev/pwm0`).

## Checklist

- [ ] Lower-half returned non-NULL before registering
- [ ] Every `*_register` return value checked
- [ ] Init guarded by the matching `CONFIG_*` symbol
- [ ] Source added to `src/CMakeLists.txt`
- [ ] Pins from the chip pinmap, not redefined in `board.h`
