/** @file essentials.c
 *  @brief Implentation of useful functions for Atmega. 
 *
 *  !!!This is only tested with Atmega8 and Atmega16
 *
 *  @author Julian Kaltenhofer
 */

#include "essentials.h"

/**
 *  @brief Waits for a maxium of 65535 ms.
 *
 *  uses Timer 2, prescaler is 64
 *
 *  @param delay value in ms
 *  @return none
 */
void
wait_ms (uint16_t delay) {
	uint16_t i;

	TCNT2 = 0;
	TCCR2 = 0b00000011;		// timer 2 enabled, prescaler 64

	for(i = 0; i < delay; i++){
		while(TCNT2 < 249);	// 250 * 64 / 16MHz = 1ms
		TCNT2 = 0;
	}
	TCCR2 = 0;
}

/**
 *  @brief Initializes the ADC.
 *
 *  set left adjust result, save the highest 8 bit in ADCH
 *  set prescaler to 64
 *  enable ADC
 *
 *  @param none
 *  @return none
 */
void
ADC_init (void) {
	ADMUX = _BV(ADLAR);					// left adjust right
	ADCSRA = _BV(ADPS1) | _BV(ADPS2);	// prescaler 64
	ADCSRA |= _BV(ADEN);	            // enable ADC, enable ADC interrupt
	
	ADC_dummy_readout();
}

/**
 *  @brief Read ADC to discard wrong value.
 *
 *  after channel change a dummy readout is required
 *  guarantees to get the correct ADC value
 *
 *  @param none
 *  @return none
 */
void
ADC_dummy_readout (void) {
	ADCSRA |= _BV(ADSC);		// start dummy-readout conversion
	while(ADCSRA & _BV(ADSC));  // wait for completion of conversion
}

/**
 *  @brief Read the specified ADC channel.
 *
 *  Read mode: single conversion
 *
 *  @param channel channel to be read
 *  @return highest 8 bit of 10 bit measurement
 */
uint8_t
ADC_read (uint8_t channel) {
	// choose channel witout changing settings
	ADMUX |= channel & 0x1f;
	
	// convert
	ADCSRA |= _BV(ADSC);        // start conversion
	while (ADCSRA & _BV(ADSC)); // wait for completion of conversion

	return ADCH;
}

/**
 *  @brief Read the specified ADC channel.
 *
 *  Read mode: single conversion
 *
 *  @param channel channel to be read
 *  @param n specify the number of measurements
 *  @return averaged measurement
 */
uint8_t
ADC_read_avg (uint8_t channel, uint8_t n) {
	uint16_t result = 0;
	uint8_t i = 0;

	for (i = 0; i < n; i++)
		result += ADC_read(channel);

	return (uint8_t)(result / n);
}