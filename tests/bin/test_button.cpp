/**
 * @file test_buttons.cpp
 *
 * @brief Test Buttons
 *
 * @date 09/2024
 */

#include "test_core.hpp"
#include "button.hpp"

int main() {
    test_core_init();
    Button button(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

    while (true) {
        if (button.is_pressed()) {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        }
    }
}
