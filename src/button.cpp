/**
 * @file button.cpp
 *
 * @brief Proxy Button class source
 *
 * @date 09/2024
 */

#include "button.hpp"

Button::Button(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState pressed_state) :
    port(port), pin(pin), pressed_state(pressed_state) { }

bool Button::is_pressed() {
    return HAL_GPIO_ReadPin(this->port, this->pin) == this->pressed_state;
}
