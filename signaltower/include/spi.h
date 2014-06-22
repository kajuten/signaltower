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
extern uint8_t spi_xfer (uint8_t data);

#endif // SPI_H
