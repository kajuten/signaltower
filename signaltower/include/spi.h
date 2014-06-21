/** @file spi.h
 *  @brief Function prototypes for the Atmegas SPI.
 *
 *  !!!This is only tested with Atmega8 and Atmega16
 *
 *  @author Julian Kaltenhofer
 */

#ifndef SPI_H
#define SPI_H

#include "essentials.h"
 
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

/*
 * Function prototypes
 */
 
/**
 *  @brief Initialize spi as master.
 *
 *  interrupt driven
 *
 *  @param none
 *  @return none
 */
extern void spi_master_init (void);

/**
 *  @brief Initialize spi as slave.
 *
 *  interrupt driven
 *
 *  @param none
 *  @return none
 */
extern void spi_slave_init (void);

/**
 *  @brief Transfer 8 bit data over spi.
 *
 *  @param data value to transmit
 *  @return received value
 */
extern uint8_t spi_xfer (unint8_t data);

#endif // SPI_H