#include "include/essentials.h"
#include "include/debounce.h"


ISR(TIMER0_OVF_vect)      
/*************************************************************************
Function: TIMER 0 Overflow interrupt
Purpose:  fires every 10ms an interrupt
**************************************************************************/
{
    static uint8_t ct0, ct1, rpt;
    uint8_t i;
 
    TCNT0 = (uint8_t)(int16_t)-(F_CPU / 1024 * 10e-3 + 0.5);  // preload for 10ms
 
    i = key_state ^ ~KEY_PIN;                       // key changed ?
    ct0 = ~(ct0 & i);                             // reset or count ct0
    ct1 = ct0 ^ (ct1 & i);                          // reset or count ct1
    i &= ct0 & ct1;                                 // count until roll over ?
    key_state ^= i;                                 // then toggle debounced state
    key_press |= key_state & i;                     // 0->1: key press detect
 
    if((key_state & REPEAT_MASK) == 0) {            // check repeat function
        rpt = REPEAT_START;                          // start delay
	}
    if(--rpt == 0) {
        rpt = REPEAT_NEXT;                            // repeat delay
        key_rpt |= key_state & REPEAT_MASK;
    }
}

/*************************************************************************
Function: get_key_press()
Purpose:  check if a key has been pressed
Input:    key mask
Returns:  bit mask where the pressed key is 1
**************************************************************************/
uint8_t get_key_press(uint8_t key_mask) {
    cli();		              // read and clear atomic !
    key_mask &= key_press;    // read key(s)
    key_press ^= key_mask;	  // clear key(s)
    sei();
    return key_mask;
}
 
/*************************************************************************
Function: get_key_rpt()
Purpose:  check if a key has been long pressed
Input:    key mask
Returns:  bit mask where the pressed key is 1
**************************************************************************/
uint8_t get_key_rpt(uint8_t key_mask) {
    cli();		               // read and clear atomic !
	key_mask &= key_rpt;       // read key(s)
	key_rpt ^= key_mask;   	   // clear key(s)
    sei();
    return key_mask;
}
 
/*************************************************************************
Function: get_key_state()
Purpose:  check if a key is pressed right now
Input:    key mask
Returns:  bit mask where the pressed key is 1
**************************************************************************/
uint8_t get_key_state(uint8_t key_mask) {
    key_mask &= key_state;
    return key_mask;
}
 
/*************************************************************************
Function: get_key_ahort()
Purpose:  check if a key has been short pressed
Input:    key mask
Returns:  bit mask where the pressed key is 1
**************************************************************************/
uint8_t get_key_short(uint8_t key_mask) {
    cli();                               // read key state and key press atomic !
    return get_key_press( ~key_state & key_mask );
}

/*************************************************************************
Function: get_key_long()
Purpose:  check if a key has been long pressed
Input:    key mask
Returns:  bit mask where the pressed key is 1
**************************************************************************/
uint8_t get_key_long(uint8_t key_mask) {
    return get_key_press( get_key_rpt(key_mask) );
}

/*************************************************************************
Function: debounce_init()
Purpose:  initialize the timer and enable timer interrupt
Input:    none
Returns:  none
**************************************************************************/
void debounce_init() {
    TCCR0 = (1<<CS02)|(1<<CS00);         // divide by 1024
    TCNT0 = (uint8_t)(int16_t)-(F_CPU / 1024 * 10e-3 + 0.5);  // preload for 10ms
    TIMSK |= 1<<TOIE0;                   // enable timer interrupt
}
