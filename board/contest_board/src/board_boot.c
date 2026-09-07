/****************************************************************************
 * Contest 2026 team 316 - STM32F103ZET6 Board Initialization
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
#include <nuttx/board.h>

#include <stdint.h>
#include <stdbool.h>

#include <stm32.h>
#include <arch/board/board.h>

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Board-specific GPIO/peripheral pin configuration, implemented in the
 * sibling source files.
 */

extern int stm32_gpio_initialize(void);
extern int stm32_spi1_initialize(void);
extern int stm32_i2c1_initialize(void);

/* Application-level bring-up: registers userled/button/SPI/I2C drivers.
 * Implemented in stm32_bringup.c.
 */

extern int stm32_bringup(void);

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: stm32_boardinitialize
 *
 * Description:
 *   All STM32 architectures must provide the following entry point.  This
 *   entry point is called early in the initialization -- after all memory
 *   has been configured and mapped but before any devices have been
 *   initialized.  It is the right place to configure on-board GPIO and
 *   peripheral pins.
 *
 ****************************************************************************/

void stm32_boardinitialize(void)
{
  /* Configure GPIO for on-board LEDs and the USER button */

  stm32_gpio_initialize();

  /* Configure SPI1 pins (SCK/MISO/MOSI/NSS) */

#ifdef CONFIG_STM32_SPI1
  stm32_spi1_initialize();
#endif

  /* Configure I2C1 pins (SCL/SDA) */

#ifdef CONFIG_STM32_I2C1
  stm32_i2c1_initialize();
#endif
}

/****************************************************************************
 * Name: board_late_initialize
 *
 * Description:
 *   If CONFIG_BOARD_LATE_INITIALIZE is selected, then an additional
 *   initialization call will be performed in the boot-up sequence to a
 *   function called board_late_initialize().  board_late_initialize() will
 *   be called immediately after up_initialize() is called and just before
 *   the initial application is started. This additional initialization
 *   phase may be used, for example, to initialize board-specific device
 *   drivers.
 *
 ****************************************************************************/

#ifdef CONFIG_BOARD_LATE_INITIALIZE
void board_late_initialize(void)
{
  /* Perform any additional board initialization here */
}
#endif

/****************************************************************************
 * Name: board_app_initialize
 *
 * Description:
 *   Perform application specific initialization.  This function is never
 *   called directly from application code, but only indirectly via the
 *   (non-standard) boardctl() interface using the command BOARDIOC_INIT.
 *   NSH invokes it because CONFIG_NSH_ARCHINIT is selected.
 *
 ****************************************************************************/

int board_app_initialize(uintptr_t arg)
{
  /* Register the /dev/userleds and /dev/buttons drivers, plus any other
   * board-level device drivers.
   */

  return stm32_bringup();
}
