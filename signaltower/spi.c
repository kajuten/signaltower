/** @file spi.c
 *  @brief Implements the functions for the Atmegas SPI.
 *
 *  !!!This is only tested with Atmega8 and Atmega16
 *
 *  @author Julian Kaltenhofer
 */

#include "include/essentials.h"

/**
 *  @brief Initialize spi as master.
 *
 *  Set prescaler to fosc / 16
 *  interrupt driven
 *
 *  @param none
 *  @return none
 */
void
spi_master_init (void) {
    // set MOSI, SCK, SS as output
    DDRB |= (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);

	// set MISO as input
	DDRB &= ~(1 << DD_MISO);

	// Enable SPI
	// Set as master
	// Prescaler: fosc / 64, to let the master process other things too
	// Enable interrupts
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPIE);

	// clear SPI Interrupt Flag by reading SPSR, SPDR
	SPSR;
	SPDR;
}

/**
 *  @brief Initialize spi as slave.
 *
 *  interrupt driven
 *
 *  @param none
 *  @return none
 */
void
spi_slave_init (void) {
    // set MISO as output
    DDRB |= 1 << MISO;

	// set MOSI, SCK, SS as input
	DDRB &= ~(1 << DD_MOSI) & ~(1 << DD_SCK) & (1 << DD_SS);

	// Enable SPI
	// Prescaler: fosc / 4, to have a fast reaction time as slave
	SPCR = (1 << SPE);

	// clear SPI Interrupt Flag by reading SPSR, SPDR
	SPSR;
	SPDR;
}

/**
 *  @brief Transfer 8 bit data over spi.
 *
 *  @param data value to transmit
 *  @return received value
 */
uint8_t
spi_xfer (unint8_t data) {
    SPDR = data;

	// wait for serial transfer to complete
	while (!(SPSR & (1 << SPIF))) ;

	return SPDR;
}

//TODO: ISR
/**
 *  @brief Interrupt SPI transmission/reception complete
 */
ISR (SPI_STC_vect) {
    
}