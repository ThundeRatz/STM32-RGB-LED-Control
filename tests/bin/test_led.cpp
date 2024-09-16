/**
 * @file test_leds.cpp
 *
 * @brief Test LEDs
 *
 * @date 09/2024
 */

#include "mcu.hpp"
#include "test_core.hpp"
#include <gpio.h>

int main() {
    test_core_init();

    while (true) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);

        hal::mcu::sleep(1000);

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

        hal::mcu::sleep(1000);
    }
}
