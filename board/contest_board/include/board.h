/****************************************************************************
 * Contest 2026 team 316 - STM32F103ZET6 Board Header
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to you under the Apache License, Version
 * 2.0 (the "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.  See the License for the specific language governing
 * permissions and limitations under the License.
 *
 ****************************************************************************/

#ifndef __BOARDS_ARM_STM32_CONTEST2026_316_BOARD_INCLUDE_BOARD_H
#define __BOARDS_ARM_STM32_CONTEST2026_316_BOARD_INCLUDE_BOARD_H

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clock Configuration ******************************************************/

/* On-board crystal frequency is 8MHz (HSE) */
#define STM32_BOARD_XTAL        8000000UL

/* PLL source is HSE/1, PLL multiplier is 9:
 *      PLL frequency is 8MHz (XTAL) x 9 = 72MHz
 */
#define STM32_CFGR_PLLSRC       RCC_CFGR_PLLSRC
#define STM32_CFGR_PLLXTPRE     0
#define STM32_CFGR_PLLMUL       RCC_CFGR_PLLMUL_CLKx9
#define STM32_PLL_FREQUENCY     (9 * STM32_BOARD_XTAL)

/* Use the PLL and set the SYSCLK source to be the PLL */
#define STM32_SYSCLK_SW         RCC_CFGR_SW_PLL
#define STM32_SYSCLK_SWS        RCC_CFGR_SWS_PLL
#define STM32_SYSCLK_FREQUENCY  STM32_PLL_FREQUENCY

/* AHB clock (HCLK) is SYSCLK (72MHz) */
#define STM32_RCC_CFGR_HPRE     RCC_CFGR_HPRE_SYSCLK
#define STM32_HCLK_FREQUENCY    STM32_PLL_FREQUENCY

/* APB2 clock (PCLK2) is HCLK (72MHz) */
#define STM32_RCC_CFGR_PPRE2    RCC_CFGR_PPRE2_HCLK
#define STM32_PCLK2_FREQUENCY   STM32_HCLK_FREQUENCY
#define STM32_APB2_CLKIN        (STM32_PCLK2_FREQUENCY)

/* APB1 clock (PCLK1) is HCLK/2 (36MHz, max 36 MHz) */
#define STM32_RCC_CFGR_PPRE1    RCC_CFGR_PPRE1_HCLKd2
#define STM32_PCLK1_FREQUENCY   (STM32_HCLK_FREQUENCY / 2)

/* APB1 timers 2-7 will be twice PCLK1 */
#define STM32_APB1_TIM2_CLKIN   (2 * STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM3_CLKIN   (2 * STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM4_CLKIN   (2 * STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM5_CLKIN   (2 * STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM6_CLKIN   (2 * STM32_PCLK1_FREQUENCY)
#define STM32_APB1_TIM7_CLKIN   (2 * STM32_PCLK1_FREQUENCY)

/* APB2 timers 1 and 8 will receive PCLK2 */
#define STM32_APB2_TIM1_CLKIN   (STM32_PCLK2_FREQUENCY)
#define STM32_APB2_TIM8_CLKIN   (STM32_PCLK2_FREQUENCY)

/* Timer Frequencies, if APBx is set to 1, frequency is same to APBx
 * otherwise frequency is 2xAPBx.  Note: TIM1,8 are on APB2, others on APB1
 */
#define BOARD_TIM1_FREQUENCY    STM32_HCLK_FREQUENCY
#define BOARD_TIM2_FREQUENCY    STM32_HCLK_FREQUENCY
#define BOARD_TIM3_FREQUENCY    STM32_HCLK_FREQUENCY
#define BOARD_TIM4_FREQUENCY    STM32_HCLK_FREQUENCY

/* USART Configuration ******************************************************/

/* USART1: PA9=TX, PA10=RX (connected to ST-Link VCP or USB-UART adapter) */
#define GPIO_USART1_TX  (GPIO_ALT | GPIO_CNF_AFPP | GPIO_MODE_50MHz | \
                         GPIO_PORTA | GPIO_PIN9)
#define GPIO_USART1_RX  (GPIO_INPUT | GPIO_CNF_INPUPD | GPIO_MODE_INPUT | \
                         GPIO_PORTA | GPIO_PIN10)

/* USART2: PA2=TX, PA3=RX (available for additional communication) */
#define GPIO_USART2_TX  (GPIO_ALT | GPIO_CNF_AFPP | GPIO_MODE_50MHz | \
                         GPIO_PORTA | GPIO_PIN2)
#define GPIO_USART2_RX  (GPIO_INPUT | GPIO_CNF_INPUPD | GPIO_MODE_INPUT | \
                         GPIO_PORTA | GPIO_PIN3)

/* SPI Configuration ********************************************************/

/* SPI1: PA5=SCK, PA6=MISO, PA7=MOSI, PA4=NSS (software controlled) */
#define GPIO_SPI1_SCK   (GPIO_ALT | GPIO_CNF_AFPP | GPIO_MODE_50MHz | \
                         GPIO_PORTA | GPIO_PIN5)
#define GPIO_SPI1_MISO  (GPIO_INPUT | GPIO_CNF_INFLOAT | GPIO_MODE_INPUT | \
                         GPIO_PORTA | GPIO_PIN6)
#define GPIO_SPI1_MOSI  (GPIO_ALT | GPIO_CNF_AFPP | GPIO_MODE_50MHz | \
                         GPIO_PORTA | GPIO_PIN7)
#define GPIO_SPI1_NSS   (GPIO_OUTPUT | GPIO_CNF_OUTPP | GPIO_MODE_50MHz | \
                         GPIO_OUTPUT_SET | GPIO_PORTA | GPIO_PIN4)

/* I2C Configuration ********************************************************/

/* I2C1: PB6=SCL, PB7=SDA */
#define GPIO_I2C1_SCL   (GPIO_ALT | GPIO_CNF_AFOD | GPIO_MODE_50MHz | \
                         GPIO_PORTB | GPIO_PIN6)
#define GPIO_I2C1_SDA   (GPIO_ALT | GPIO_CNF_AFOD | GPIO_MODE_50MHz | \
                         GPIO_PORTB | GPIO_PIN7)

/* LED Configuration ********************************************************/

/* LEDs on PB0, PB1, PB5 */
#define GPIO_LED1       (GPIO_OUTPUT | GPIO_CNF_OUTPP | GPIO_MODE_50MHz | \
                         GPIO_OUTPUT_CLEAR | GPIO_PORTB | GPIO_PIN0)
#define GPIO_LED2       (GPIO_OUTPUT | GPIO_CNF_OUTPP | GPIO_MODE_50MHz | \
                         GPIO_OUTPUT_CLEAR | GPIO_PORTB | GPIO_PIN1)
#define GPIO_LED3       (GPIO_OUTPUT | GPIO_CNF_OUTPP | GPIO_MODE_50MHz | \
                         GPIO_OUTPUT_CLEAR | GPIO_PORTB | GPIO_PIN5)

/* Button Configuration ****************************************************/

/* USER button (typically on PA0) */
#define GPIO_BTN_USER   (GPIO_INPUT | GPIO_CNF_INPUPD | GPIO_MODE_INPUT | \
                         GPIO_PORTA | GPIO_PIN0)

/* ADC Configuration ********************************************************/

/* ADC1: PA0 (shared with USER button), PA1, PA2 */
#define GPIO_ADC1_IN0   (GPIO_INPUT | GPIO_CNF_ANALOG | GPIO_MODE_INPUT | \
                         GPIO_PORTA | GPIO_PIN0)
#define GPIO_ADC1_IN1   (GPIO_INPUT | GPIO_CNF_ANALOG | GPIO_MODE_INPUT | \
                         GPIO_PORTA | GPIO_PIN1)
#define GPIO_ADC1_IN2   (GPIO_INPUT | GPIO_CNF_ANALOG | GPIO_MODE_INPUT | \
                         GPIO_PORTA | GPIO_PIN2)

/* PWM Configuration ********************************************************/

/* TIM1: PA8 (CH1) */
#define GPIO_TIM1_CH1   (GPIO_ALT | GPIO_CNF_AFPP | GPIO_MODE_50MHz | \
                         GPIO_PORTA | GPIO_PIN8)

/* TIM2: PA0 (CH1), PA1 (CH2) - shared with ADC/USER button */
#define GPIO_TIM2_CH1   (GPIO_ALT | GPIO_CNF_AFPP | GPIO_MODE_50MHz | \
                         GPIO_PORTA | GPIO_PIN0)
#define GPIO_TIM2_CH2   (GPIO_ALT | GPIO_CNF_AFPP | GPIO_MODE_50MHz | \
                         GPIO_PORTA | GPIO_PIN1)

/* JTAG/SWD Configuration **************************************************/

/* Enable SWD (PA13=SWDIO, PA14=SWCLK), disable JTAG to free PB3/PB4 */
#define GPIO_SWDIO      (GPIO_ALT | GPIO_CNF_AFPP | GPIO_MODE_50MHz | \
                         GPIO_PORTA | GPIO_PIN13)
#define GPIO_SWCLK      (GPIO_ALT | GPIO_CNF_AFPP | GPIO_MODE_50MHz | \
                         GPIO_PORTA | GPIO_PIN14)

#endif /* __BOARDS_ARM_STM32_CONTEST2026_316_BOARD_INCLUDE_BOARD_H */
