#include "stdio.h"
#include "pico/stdlib.h"

#include "potentiometer.h"
#include "gauge.h"

int main(int argc, char* argv[]) {
    stdio_init_all();

    printf("# Starting picopotgauge\n");
    pot_init();
    gauge_init();

    while (true) {
        uint8_t pot = pot_scaled(26);        // GPIO26 is ADC0 on Pico
        printf("%3d:%*s\n", pot, pot, "<->");
        sleep_ms(30);
    }
}