# Name: prepare.cmake
# ThundeRatz Robotics Team
# Brief: This file contains a script to prevent issues with multiple Callback definitions
# 01/2024

set(CALLBACK "void HAL_TIM_PeriodElapsedCallback")
set(WEAK_CALLBACK "__attribute__((weak)) void HAL_TIM_PeriodElapsedCallback")
set(MAIN_FILE ../cube/Src/main.c)

file(READ ${MAIN_FILE} MAIN_CONTENTS)

string(FIND "${MAIN_CONTENTS}" ${WEAK_CALLBACK} WEAK_POS)
if (${WEAK_POS} EQUAL -1)
    string(REPLACE ${CALLBACK} ${WEAK_CALLBACK} MAIN_CONTENTS "${MAIN_CONTENTS}")
    file(WRITE ${MAIN_FILE} "${MAIN_CONTENTS}")
endif()
