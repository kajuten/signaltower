/** @file spi.c
 *  @brief Implements the functions for the Atmegas SPI.
 *
 *  !!!This is only tested with Atmega8 and Atmega16
 *
 *  @author Julian Kaltenhofer
 */

#include "include/essentials.h"
#include "include/spi.h"


#if defined(__AVR_ATmega8__)
 #define PORT_SPI  PORTB
 #define DDR_SPI   DDRB
 #define DD_SS     DDB2
 #define DD_MOSI   DDB3
 #define DD_MISO   DDB4
 #define DD_SCK    DDB5
#elif defined(__AVR_ATmega16__)
 #define PORT_SPI  PORTB
 #define DDR_SPI   DDRB
 #define DD_SS     DDB4
 #define DD_MOSI   DDB5
 #define DD_MISO   DDB6
 #define DD_SCK    DDB7
#else
 #error "No SPI definition for MCU available"
#endif

/**
 *  @brief Initialize spi as master.
 *
 *  Set prescaler to fosc / 16
 *
 *  @param none
 *  @return none
 */
void
spi_master_init (void) {
    uint8_t tmp;

   // set MOSI, SCK, SS as output
    DDRB |= (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);

	// set MISO as input
	DDRB &= ~(1 << DD_MISO);

	// Enable SPI
	// Set as master
	// Prescaler: fosc / 16, to let the master process other things too
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);

	// clear SPI Interrupt Flag by reading SPSR, SPDR
	tmp = SPSR;
	tmp = SPDR;
}

/**
 *  @brief Initialize spi as slave.
 *
 *  @param none
 *  @return none
 */
void
spi_slave_init (void) {
    uint8_t tmp;
    // set MISO as output
    DDRB |= 1 << DD_MISO;

	// set MOSI, SCK, SS as input
	DDRB &= ~((1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS));

	// Enable SPI
	// Prescaler: fosc / 4, to have a fast reaction time as slave
	SPCR = (1 << SPE);

	// clear SPI Interrupt Flag by reading SPSR, SPDR
	tmp = SPSR;
	tmp = SPDR;
}

/**
 *  @brief Transfer 8 bit data over spi.
 *
 *  @param data value to transmit
 *  @return received value
 */
uint8_t
spi_xfer (uint8_t data) {
    PORT_SPI &= ~(1 << DD_SS);
    SPDR = data;

	// wait for serial transfer to complete
	while (!(SPSR & (1 << SPIF))) ;

	PORT_SPI |= 1 << DD_SS;

	return SPDR;
}
/*
//TODO: ISR
/**
 *  @brief Interrupt SPI transmission/reception complete
 *
ISR (SPI_STC_vect) {
    while (!(SPSR & (1 << SPIF))) ;
    result = SPDR;
    uart_putc(result);
    PORTB = PORTB ^ 0x0f;
}
*/
