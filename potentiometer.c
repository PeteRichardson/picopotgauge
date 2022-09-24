#include <stdio.h>
#include <stdlib.h>       // abs()
#include "hardware/adc.h" // adc_*()

#include "potentiometer.h"

uint16_t raw;           // = value direct from 12-bit adc
                        //    NOTE: HW may limit raw values e.g. joystick
                        //    that doesn't physically reach pot's max.
uint16_t prevRaw;       // = previous adc value. Used to smooth output
uint8_t scaled;         // = value after scaling to SCALED_MIN...SCALED_MAX


inline uint8_t scale(uint16_t raw) {
    return SCALED_MIN + raw * SCALED_MAX/4096;
}

void pot_init(int gpio) {
    printf("# Pot init starting");
    adc_init();
    adc_gpio_init(gpio);
    adc_select_input(0);

    printf("# Pot init complete!");
}

uint8_t pot_scaled() {
    raw = adc_read();                     // Get a new 12 bit ADC val
    if (abs(raw - prevRaw) > MOVE_THRESHOLD) { // If it's a big enough move
        scaled =  scale(raw);                                  // ..scale
        prevRaw = raw;                  // NOTE: this must be inside the if.
    };
    return scaled;
}
