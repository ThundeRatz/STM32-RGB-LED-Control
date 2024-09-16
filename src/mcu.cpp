/**
 * @file mcu.cpp
 *
 * @brief MCU related
 */

#include <stdint.h>

#include "mcu.hpp"

#include <dma.h>
#include "gpio.h"

/*****************************************
 * Public Function Body Definitions
 *****************************************/

namespace hal {
void mcu::init(void) {
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();

    MX_DMA_Init();
}

void mcu::sleep(uint32_t ms) {
    HAL_Delay(ms);
}
}  // namespace hal
