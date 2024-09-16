/**
 * @file test_leds.cpp
 *
 * @brief Test LEDs
 *
 * @date 09/2024
 */

#include "mcu.hpp"
#include "test_core.hpp"
#include "stm32f1xx_hal.h"  // Include the correct HAL header for STM32

int main() {
    test_core_init();

    while (true) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

        hal::mcu::sleep(1000);

        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

        hal::mcu::sleep(1000);
    }
}
