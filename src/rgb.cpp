/**
 * @file rgb.cpp
 *
 * @brief RGB class implementation
 *
 * @date 09/2024
 */

#include "rgb.hpp"
#include "utils.hpp"

RGB::RGB(
    TIM_HandleTypeDef* handle, void (*init_function)(), uint32_t red_channel, uint32_t green_channel,
    uint32_t blue_channel
) :
    handle(handle), red_channel(red_channel), green_channel(green_channel), blue_channel(blue_channel) {
    init_function();

    HAL_TIM_PWM_Start(handle, red_channel);
    HAL_TIM_PWM_Start(handle, green_channel);
    HAL_TIM_PWM_Start(handle, blue_channel);

    this->set_color(0, 0, 0);
}

void RGB::set_color(uint8_t red, uint8_t green, uint8_t blue) {
    uint16_t red_compare = utils::map(red, 0U, 255, 0, 2000);
    uint16_t green_compare = utils::map(green, 0, 255, 0, 2000);
    uint16_t blue_compare = utils::map(blue, 0, 255, 0, 2000);

    __HAL_TIM_SET_COMPARE(handle, red_channel, red_compare);
    __HAL_TIM_SET_COMPARE(handle, green_channel, green_compare);
    __HAL_TIM_SET_COMPARE(handle, blue_channel, blue_compare);
}
