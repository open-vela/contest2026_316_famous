/****************************************************************************
 * Contest 2026 team 316 - STM32F103ZET6 Button Driver
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <errno.h>

#include <nuttx/arch.h>
#include <nuttx/board.h>
#include <arch/board/board.h>

#include <stm32.h>

#if defined(CONFIG_ARCH_BUTTONS)

/****************************************************************************
 * Private Data
 ****************************************************************************/

#define NUM_BUTTONS 1

/* This array maps a button index to its GPIO pin configuration.
 * USER button = PA0 (active low).
 */

static const uint32_t g_buttons[NUM_BUTTONS] =
{
  GPIO_BTN_USER
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_button_initialize
 *
 * Description:
 *   board_button_initialize() must be called to initialize button resources.
 *   After that, board_buttons() may be called to collect the current state
 *   of all buttons or board_button_irq() may be called to register button
 *   interrupt handlers.
 *
 ****************************************************************************/

uint32_t board_button_initialize(void)
{
  /* Configure the GPIO pin as an input.  NOTE that EXTI interrupts are
   * configured for all pins.
   */

  stm32_configgpio(g_buttons[0]);

  return NUM_BUTTONS;
}

/****************************************************************************
 * Name: board_buttons
 ****************************************************************************/

uint32_t board_buttons(void)
{
  uint32_t ret = 0;

  /* A LOW value means that the key is pressed. */

  bool released = stm32_gpioread(g_buttons[0]);

  /* Accumulate the set of depressed (not released) keys */

  if (!released)
    {
      ret |= (1 << 0);
    }

  return ret;
}

/****************************************************************************
 * Name: board_button_irq
 ****************************************************************************/

#ifdef CONFIG_ARCH_IRQBUTTONS
int board_button_irq(int id, xcpt_t irqhandler, void *arg)
{
  int ret = -EINVAL;

  if (id >= 0 && id < NUM_BUTTONS)
    {
      ret = stm32_gpiosetevent(g_buttons[id], true, true, true, irqhandler,
                               arg);
    }

  return ret;
}
#endif

#endif /* CONFIG_ARCH_BUTTONS */
