#include "include/essentials.h"
#include "include/debounce.h"
#include "include/spi.h"
#include "include/uart.h"

int
main (int argc, char **argv) {
    PORTB = 0;
    DDRB |= 0x0f;

    spi_slave_init();
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));

	sei();

    uart_puts("Hello World\n");

	while (1) {
	    ;
	}

    return 0;
}
