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
    Button button(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);

    while (true) {
        if (button.is_pressed()) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
        } else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
        }
    }
}
