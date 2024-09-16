/**
 * @file rgb.hpp
 *
 * @brief RGB class
 *
 * @date 09/2024
 */

#ifndef RGB_HPP
#define RGB_HPP

#include <gpio.h>
#include <tim.h>

/**
 * @brief Class for controlling an RGB LED
 */
class RGB {
public:
    /**
     * @brief Constructor for RGB class
     *
     * @param tim_handler Pointer to HAL timer
     * @param red_channel Red channel number
     * @param green_channel Green channel number
     * @param blue_channel Blue channel number
     */
    RGB(TIM_HandleTypeDef* handle, void (*init_function)(), uint32_t red_channel, uint32_t green_channel,
        uint32_t blue_channel);

    /**
     * @brief Set the RGB LED color
     *
     * @param red   Red color intensity
     * @param green Green color intensity
     * @param blue  Blue color intensity
     */
    void set_color(uint8_t red, uint8_t green, uint8_t blue);

private:
    TIM_HandleTypeDef* handle;

    uint32_t red_channel;
    uint32_t green_channel;
    uint32_t blue_channel;
};

#endif  // RGB_HPP
