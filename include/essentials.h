#ifndef ESSENTIALS_H
#define	ESSENTIALS_H

/////////////////////////////////////////////////////////////////////////////////////////
#include <avr/io.h>

/**
 * Important macros in avr/sfr_defs.h:
 *
 * Bit manipulation
 *	#define 	_BV(bit)   (1 << (bit))
 *
 * IO register bit manipulation
 *	#define 	bit_is_set(sfr, bit)                (_SFR_BYTE(sfr) & _BV(bit))
 *	#define 	bit_is_clear(sfr, bit)              (!(_SFR_BYTE(sfr) & _BV(bit)))
 *	#define 	loop_until_bit_is_set(sfr, bit)     do { } while (bit_is_clear(sfr, bit))
 *	#define 	loop_until_bit_is_clear(sfr, bit)   do { } while (bit_is_set(sfr, bit))
 */
#include <avr/sfr_defs.h>

#include <stdlib.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
 
#include "uart.h"
#include "debounce.h"
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
#define bit_set(sfr, bit)  	sfr |=(_BV(bit))
#define bit_clr(sfr, bit)  	sfr &=(~_BV(bit))

/* define CPU frequency in Mhz here if not defined in Makefile */
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define UART_BAUD_RATE 57600
/////////////////////////////////////////////////////////////////////////////////////////

/*
 * Function prototypes
 */
 
/**
 *  @brief   wait for a maxium of 65535 ms (2^16 -1)
 *
 * uses Timer 2, prescaler is 64
 *
 *  @param   delay in ms
 *  @return  none
 */
extern void wait(uint16_t delay);

/**
 *  @brief   initialize ADC
 *
 * set left adjust result, save the highest 8 bit in ADCH
 * set prescaler to 64
 * enable ADC
 *
 *  @param   none
 *  @return  none
 */
extern void ADC_init(void);

/**
 *  @brief   read ADC to discard wrong value
 *
 * after channel change a dummy readout is required
 * guarantees to get the correct ADC value
 *
 *  @param   none
 *  @return  none
 */
extern void ADC_dummy_readout(void);

/**
 *  @brief   read the specified ADC channel 
 *
 * Read mode: single conversion
 *
 *  @param   channel channel to be read
 *  @return  measurement
 */
extern uint8_t ADC_read(uint8_t channel);

/**
 *  @brief   read the specified ADC channel 
 *
 * Read mode: single conversion
 *
 *  @param   channel channel to be read
 *  @param   n specify the number of measurements
 *  @return  averaged measurement
 */
extern uint8_t ADC_read_avg(uint8_t channel, uint8_t n);

#endif