/**
 * @file button.hpp
 *
 * @brief Proxy Button class header
 *
 * @date 09/2024
 */

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <cstdint>
#include <gpio.h>

/**
 * @brief Class for acquiring a button data
 */
class Button {
public:
    /**
     * @brief Constructor for Button class
     *
     * @param port GPIO port
     * @param pin GPIO pin
     * @param pressed_state GPIO pin state when button is pressed
     */
    Button(GPIO_TypeDef* port, uint16_t pin, GPIO_PinState pressed_state = GPIO_PIN_SET);

    /**
     * @brief Check if button is pressed
     *
     * @return bool True if button is pressed, false otherwise
     */
    bool is_pressed();

private:
    GPIO_TypeDef* port;
    uint16_t      pin;
    GPIO_PinState pressed_state;
};

#endif  // BUTTON_HPP
