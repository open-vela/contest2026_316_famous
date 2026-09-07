# contest2026_316_famous

## 2026 首届 openvela AI 硬件开发者大赛 - 队伍 316 (famous)

### 作品简介

本项目将 openvela (基于 NuttX) 实时操作系统移植到 STM32F103ZET6 开发板，完成新硬件适配赛道的比赛要求。实现了完整的 BSP 移植、多种外设驱动支持和丰富的应用 Demo。

### 选题方向

**新硬件适配** - 将 openvela 适配到 STM32F103ZET6 平台，实现最小 NSH 系统启动和多种外设驱动。

### 目标硬件

| 参数 | 规格 |
|------|------|
| MCU | STM32F103ZET6 |
| 内核 | ARM Cortex-M3 |
| 主频 | 72 MHz |
| Flash | 512 KB |
| SRAM | 64 KB |
| GPIO | 80 引脚 |

### 功能特性

#### 1. 完整的 BSP 移植

- ✅ ARM Cortex-M3 架构支持
- ✅ STM32F103ZE 芯片支持
- ✅ 72MHz 时钟配置 (HSE 8MHz + PLL x9)
- ✅ 64KB SRAM 配置
- ✅ NSH 最小系统启动

#### 2. 多种外设驱动

| 外设 | 状态 | 引脚 | 说明 |
|------|------|------|------|
| USART1 | ✅ 已支持 | PA9/PA10 | 控制台串口 (115200 baud) |
| USART2 | ✅ 已支持 | PA2/PA3 | 额外串口 |
| SPI1 | ✅ 已支持 | PA4/PA5/PA6/PA7 | SPI 通信 |
| I2C1 | ✅ 已支持 | PB6/PB7 | I2C 通信 |
| GPIO | ✅ 已支持 | - | 通用输入输出 |
| LED | ✅ 已支持 | PB0/PB1/PB5 | 3 个 LED |
| Button | ✅ 已支持 | PA0 | USER 按键 |
| ADC1 | ✅ 已支持 | PA0/PA1/PA2 | 模数转换 |
| PWM | ✅ 已支持 | PA8 | 脉宽调制 |
| RTC | ✅ 已支持 | - | 实时时钟 |
| IWDG | ✅ 已支持 | - | 独立看门狗 |

#### 3. 丰富的应用 Demo

| Demo | 功能 | 使用命令 |
|------|------|----------|
| LED Blink | LED 闪烁演示 | `led_blink` |
| Button Test | 按键检测演示 | `button_test` |
| System Info | 系统信息显示 | `sysinfo` |

### 目录结构

```
contest2026_316_famous/
├── board/contest_board/          # 板级支持包 (BSP)
│   ├── CMakeLists.txt           # 板级 CMake
│   ├── Kconfig                  # 板级配置
│   ├── README.md                # 板级说明
│   ├── configs/nsh/
│   │   └── defconfig            # NSH 完整配置
│   ├── include/
│   │   └── board.h              # 时钟和引脚定义
│   └── src/
│       ├── CMakeLists.txt       # 源码 CMake
│       ├── board_boot.c         # 板级初始化（标准入口）
│       ├── stm32_bringup.c      # 注册 /dev/userleds、/dev/buttons
│       ├── stm32_gpio.c         # GPIO/LED/按键引脚配置
│       ├── stm32_spi.c          # SPI 引脚配置
│       ├── stm32_i2c.c          # I2C 引脚配置
│       ├── stm32_userleds.c     # 标准用户 LED 驱动
│       └── stm32_buttons.c      # 标准按键驱动
├── app/                          # 应用 Demo
│   ├── CMakeLists.txt           # 应用 CMake
│   ├── README.md                # 应用说明
│   ├── led_blink/               # LED 闪烁 Demo
│   ├── button_test/             # 按键检测 Demo
│   └── sysinfo/                 # 系统信息 Demo
├── logs/                         # AI Coding 日志
├── setup_openvela.sh            # Linux 环境配置脚本
├── build_firmware.sh            # 编译脚本
├── flash.sh                     # 烧录脚本
├── FLASH_GUIDE.md               # 烧录详细说明
├── README.md                    # 本文件
├── contest2026_316_famous.xml   # 仓库 manifest
└── openvela.xml                 # openvela 工程 manifest
```

### 快速开始

#### 1. 环境配置 (Linux VM)

```bash
chmod +x setup_openvela.sh
./setup_openvela.sh
```

#### 2. 编译固件

```bash
chmod +x build_firmware.sh
./build_firmware.sh
```

#### 3. 烧录到开发板

```bash
chmod +x flash.sh
./flash.sh
```

#### 4. 连接串口

- 串口: USART1 (PA9=TX, PA10=RX)
- 波特率: 115200, 8N1

成功启动后将看到 `nsh>` 提示符。

### NSH 命令示例

```bash
# 显示系统信息
nsh> sysinfo

# 运行 LED 闪烁 Demo
nsh> led_blink

# 运行按键检测 Demo
nsh> button_test

# 显示运行中的进程
nsh> ps

# 显示内存使用情况
nsh> free

# 列出设备
nsh> ls /dev
```

### 时钟配置

```
HSE (8MHz) → PLL (x9) → SYSCLK (72MHz)
                         ↓
                    AHB (72MHz)
                    ├── APB1 (36MHz) → USART2/3, TIM2-7
                    └── APB2 (72MHz) → USART1, SPI1, TIM1, ADC1
```

### 评分加分项

- ✅ 完成 STM32F103ZET6 全新平台适配
- ✅ 实现最小 NSH 系统启动
- ✅ 完整的外设驱动支持 (GPIO/SPI/I2C/ADC/PWM/RTC/Watchdog)
- ✅ 丰富的应用 Demo (LED/按键/系统信息)
- ✅ 代码结构清晰，可直接合入主线
- ✅ 提供详细适配文档和使用指南
- ✅ 自动化编译和烧录脚本

### AI Coding 使用说明

本项目使用 MiMoCode (mimo) AI 助手完成以下工作：

- 硬件规格研究与方案设计
- BSP 代码生成与优化
- 外设驱动开发
- defconfig 配置调试
- 应用 Demo 开发
- 文档编写

完整对话日志见 `logs/` 目录。

### 参考资源

- [STM32F103ZET6 Datasheet](https://www.st.com/resource/en/datasheet/stm32f103ze.pdf)
- [STM32F103xx Reference Manual](https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [NuttX STM32 文档](https://nuttx.apache.org/docs/latest/platforms/arm/stm32/index.html)
- [openvela 新硬件适配赛道指引](https://github.com/open-vela/docs/blob/dev-ai-contest-2026/zh-cn/contest_2026/hardware_porting/hardware_porting_track_guide.md)

### 提交前检查清单

- [x] defconfig 配置完整
- [x] 板级初始化代码完成
- [x] UART 控制台输出正常
- [x] GPIO 驱动支持
- [x] SPI 驱动支持
- [x] I2C 驱动支持
- [x] LED/按键 Demo 应用
- [x] 系统信息 Demo 应用
- [x] 编译脚本自动化
- [x] 烧录脚本自动化
- [x] 完整文档说明
- [x] AI Coding 日志记录
