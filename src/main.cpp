/**
 * @file main.cpp
 *
 * @brief Main function
 */

#include <adc.h>
#include <tim.h>
#include "mcu.hpp"
#include "potentiometer.hpp"
#include "rgb.hpp"
#include "button.hpp"

/*****************************************
 * Private Constant Definitions
 *****************************************/

static constexpr uint16_t led_toggle_delay_ms = 1500;

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    hal::mcu::init();

    Button        button(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    Potentiometer potentiometer(&hadc, MX_ADC_Init);
    RGB           rgb(&htim2, MX_TIM2_Init, TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3);

    for (;;) {
        if (button.is_pressed()) {
            rgb.set_color(255, 255, 255);
        } else {
            uint16_t potentiometer_value = potentiometer.get_value();
            rgb.set_color(potentiometer_value >> 8, potentiometer_value >> 8, potentiometer_value >> 8);
        }
    }
}
