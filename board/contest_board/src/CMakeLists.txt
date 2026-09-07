# Contest 2026 team 316 - STM32F103ZET6 Board Source
# NOTE: the `board` library target is already created by boards/CMakeLists.txt
# (nuttx_add_kernel_library(board ...)); only add our sources to it here.
target_sources(board PRIVATE
  board_boot.c
  stm32_gpio.c
  stm32_spi.c
  stm32_i2c.c
  stm32_bringup.c
  stm32_userleds.c
  stm32_buttons.c
)
