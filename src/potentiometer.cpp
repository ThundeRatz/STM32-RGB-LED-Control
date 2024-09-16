/**
 * @file potentiometer.cpp
 *
 * @brief Potentiometer class implementation
 *
 * @date 09/2024
 */

#include "potentiometer.hpp"

Potentiometer::Potentiometer(ADC_HandleTypeDef* handle, void (*init_function)()) : handle(handle) {
    init_function();
    HAL_ADC_Start_DMA(this->handle, this->buffer.data(), 1);
}

uint16_t Potentiometer::get_value() {
    return static_cast<uint16_t>(this->buffer.at(0));
}
