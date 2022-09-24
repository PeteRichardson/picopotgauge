cmake_minimum_required(VERSION 3.18)

include(pico_sdk_import.cmake)

project(picopotgauge)

add_executable(${PROJECT_NAME}
    main.c potentiometer.c gauge.c
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_adc
    hardware_pwm
)

pico_sdk_init()

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})