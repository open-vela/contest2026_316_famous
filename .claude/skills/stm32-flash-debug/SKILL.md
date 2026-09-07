---
name: stm32-flash-debug
description: Use this skill when flashing the STM32F103ZET6 fails, the debugger cannot connect, or the board does not boot after flashing. Covers checking the ST-Link connection, verifying the firmware format (ELF/HEX/BIN), and resolving common openocd / st-flash errors.
metadata:
  origin: contest2026_316_famous
---

# STM32 Flash Debug

Diagnose and fix STM32F103ZET6 flashing and boot problems. Use this skill
when flashing fails or the board does not start after a flash.

## When to Activate

- `st-flash` or `openocd` cannot connect to the target.
- Flashing succeeds but the board does not run (no `nsh>` prompt).
- Firmware format errors (wrong entry point, wrong base address).
- "Error: init mode failed" / "Can not connect to target" / "target not halted".

## 1. Check the ST-Link Connection

```bash
# Confirm the probe is visible over USB
lsusb | grep -i stlink          # ST-Link V2 = 0483:3748
st-info --probe                  # list probe + chip
st-info --descr                  # confirm target voltage present
```

Common wiring (STM32F103ZET6, SWD):

| ST-Link V2 pin | Board pin |
|----------------|-----------|
| SWDIO          | PA13 (SWDIO) |
| SWCLK          | PA14 (SWCLK) |
| GND            | GND |
| 3.3V           | 3.3V |

> Only SWDIO/SWCLK/GND are strictly required. Do not power from the probe if
> the board already has 5V/3.3V USB power.

## 2. Verify Firmware Format

Confirm the build produced the expected artifacts and base address:

```bash
ls -l nuttx.elf nuttx.bin nuttx.hex
arm-none-eabi-readelf -h nuttx.elf | grep Entry   # should be 0x0800xxxx
```

Required defconfig for flashable output:

```ini
CONFIG_INTELHEX_BINARY=y
CONFIG_RAW_BINARY=y
```

## 3. Flash with st-flash (ST-Link)

```bash
# Erase then write BIN to flash base 0x08000000
st-flash erase
st-flash write nuttx.bin 0x08000000
st-flash reset
```

## 4. Flash with OpenOCD

```bash
openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg \
  -c "init; halt; flash write_image erase nuttx.bin 0x08000000; reset; shutdown"
```

## 5. Common Errors and Fixes

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| `Can not connect to target` | Wrong SWD wiring / no power | Recheck PA13/PA14/GND, add power |
| `target not halted` | Boot0 boot pin / readout protection | Check BOOT0=0; unlock via `st-flash --connect-under-reset` |
| Flashed but no boot | Wrong base address or bad vector table | Verify entry `0x08000000`, check `CONFIG_ARCH_CHIP_STM32F103ZE` |
| `init mode failed` | Probe driver conflict (CH340 vs ST-Link) | Unplug other USB-UART, or `--connect-under-reset` |
| Read protection (`RDP`) set | Chip locked | `openocd ... -c "stm32f1x unlock 0; reset halt"` |

## 6. Post-Flash Verification

Connect the console USART1 (PA9=TX, PA10=RX) at 115200 8N1 and confirm:

```
nsh>
```

If the prompt does not appear, check `CONFIG_USART1_SERIAL_CONSOLE=y`,
`CONFIG_USART1_BAUD=115200`, and that BOOT0 is tied low (boot from flash).

## Checklist

- [ ] ST-Link detected with `st-info --probe`
- [ ] SWDIO/SWCLK/GND wired to PA13/PA14/GND
- [ ] `nuttx.bin` exists and entry is 0x0800xxxx
- [ ] Flash written to 0x08000000
- [ ] Console shows `nsh>` at 115200 8N1
