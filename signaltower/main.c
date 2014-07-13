#include "include/essentials.h"
#include "include/debounce.h"
#include "include/spi.h"
#include "include/uart.h"

int
main (int argc, char **argv) {
    uint8_t i, send = 0;
    PORTB = 0;
    DDRB |= 0x0f;

    spi_master_init();

    while (1) {
        for (i = 0; i < 16; i++) { // i in char: A, B, C, D, E, F
            send = spi_xfer(i);
            PORTB = send & 0x0f;
            wait_ms(2000);
        }
        wait_ms(60000);
    }

    return 0;
}
