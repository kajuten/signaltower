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
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));

    sei();

    uart_puts("Hello World\n");

    while (1) {
        for (i = 65; i < 71; i++) { // i in char: A, B, C, D, E, F
            uart_putc(i);
            send = spi_xfer(i);
            uart_putc(send);
            uart_putc('\n');
            wait_ms(500);
        }
        wait_ms(10000);
    }

    return 0;
}
