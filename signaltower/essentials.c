#include "essentials.h"

/*************************************************************************
Function: wait_ms()
Purpose:  wait for a maxium of 65535 ms (2^16 -1)
Input:    delay in ms
Returns:  none
**************************************************************************/
void wait_ms(uint16_t delay) {
	uint16_t i;

	TCNT2 = 0;
	TCCR2 = 0b00000011;		//timer 2 enabled, prescaler 64

	for(i = 0; i < delay; i++){
		while(TCNT2 < 249);	//250*64/16MHz=1ms
		TCNT2 = 0;
	}
	TCCR2 = 0;
}

/*************************************************************************
Function: ADC_init()
Purpose:  initialize ADC
Input:    none
Returns:  none
**************************************************************************/
void ADC_init(void) {
	ADMUX = _BV(ADLAR);					//left adjust right
	ADCSRA = _BV(ADPS1) | _BV(ADPS2);	//prescaler 64
	ADCSRA |= _BV(ADEN);	//enable ADC, enable ADC interrupt
	
	ADC_dummy_readout();
}

/*************************************************************************
Function: ADC_dummy_readout()
Purpose:  read ADC to discard wrong value
Input:    none
Returns:  none
**************************************************************************/
void ADC_dummy_readout(void) {
	ADCSRA |= _BV(ADSC);		//start dummy-readout conversion
	while(ADCSRA & _BV(ADSC));//wait for completion of conversion
}

/*************************************************************************
Function: ADC_read()
Purpose:  read the specified ADC channel 
Input:    channel channel to be read
Returns:  measurement
**************************************************************************/
uint8_t ADC_read(uint8_t channel) {
	//choose channel witout changing settings
	ADMUX |= channel & 0x1f;
	
	//convert
	ADCSRA |= _BV(ADSC);//start conversion
	while(ADCSRA & _BV(ADSC));//wait for completion of conversion

	return ADCH;
}

/*************************************************************************
Function: ADC_read_avg()
Purpose:  read the specified ADC channel 
Input:    channel channel to be read
		  n specify the number of measurements
Returns:  averaged measurement
**************************************************************************/
uint8_t ADC_read_avg(uint8_t channel, uint8_t n) {
	uint16_t result = 0;
	uint8_t i = 0;

	for(i = 0; i < n; i++)
		result += ADC_read(channel);

	return (uint8_t)(result / n);
}