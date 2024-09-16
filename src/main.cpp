/**
 * @file main.cpp
 *
 * @brief Main function
 */

#include <adc.h>
#include <stm32f1xx_hal_gpio.h>
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

    Button        button(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
    Potentiometer potentiometer(&hadc1, MX_ADC1_Init);
    RGB           rgb(&htim1, MX_TIM1_Init, TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3);

    for (;;) {
        if (button.is_pressed()) {
            rgb.set_color(255, 255, 255);
        } else {
            uint16_t potentiometer_value = potentiometer.get_value();
            rgb.set_color(potentiometer_value >> 8, potentiometer_value >> 8, potentiometer_value >> 8);
        }
    }
}
