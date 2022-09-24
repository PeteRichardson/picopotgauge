#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

#include "potentiometer.h"
#include "gauge.h"

#define POT_PIN 26
#define GAUGE_PIN 16


int main(int argc, char* argv[]) {
    stdio_init_all();
    sleep_ms(500);

    printf("# Starting picopotgauge\n");
    pot_init(POT_PIN);         
    gauge_init(GAUGE_PIN);

    uint8_t pot;
    uint8_t prev_pot;

    while (true) {
        uint8_t pot = pot_scaled();
        if (pot != prev_pot) { // don't bother updating if same
            prev_pot = pot;                  // NOTE: this must be inside the if.
            gauge_set_duty(pot);
            printf("%3d:%*s\n", pot, pot, "<->");
        };
        sleep_ms(10);
    }
}