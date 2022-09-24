#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#include "gauge.h"

float duty_cycle = 0.0;
uint slice;
uint channel;

void gauge_init(int gpio) {
    printf("# Gauge init starting.");
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    slice = pwm_gpio_to_slice_num(gpio);
    channel = pwm_gpio_to_channel(gpio);
    pwm_set_enabled(slice, true);

    printf("# Gauge init complete.");
}

uint32_t pwm_set_freq_duty(uint slice_num, uint chan, uint32_t f, int d) {
    uint32_t clock=125000000;
    uint32_t divider16 = clock / f / 4096 + (clock % (f * 4096) != 0);
    if (divider16/16 == 0)
        divider16 = 16;
    uint32_t wrap = clock * 16 / divider16 / f - 1;
    pwm_set_clkdiv_int_frac(slice_num, divider16/16, divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, chan, wrap * d / 100);
    return wrap;
}

void gauge_set_duty(float duty_cycle) {
    pwm_set_freq_duty( slice, channel, 50, duty_cycle);
    //printf("Duty cycle = %2.1f%%\n", duty_cycle);
}