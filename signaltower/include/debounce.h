#ifndef DEBOUNCE_H
#define	DEBOUNCE_H
/************************************************************************
 *                                                                      *
 *                      Debouncing 8 Keys                               *
 *                      Sampling 4 Times                                *
 *                      With Repeat Function                            *
 *                                                                      *
 *              Author: Peter Dannegger                                 *
 *                      danni@specs.de                                  *
 *                                                                      *
 ************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////
#define KEY_PIN			PINA
#define KEY1            1
#define KEY2            2
#define ALL_KEYS        (1<<KEY1 | 1<<KEY2)
 
#define REPEAT_MASK     ALL_KEYS
#define REPEAT_START    50		// after 500ms because timer interrupt every 10ms
#define REPEAT_NEXT     20      // every 200ms
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
volatile uint8_t key_state;		// debounced and inverted key state:
								// bit = 1: key pressed
volatile uint8_t key_press;		// key press detect
volatile uint8_t key_rpt; 		// key long press and repeat
/////////////////////////////////////////////////////////////////////////////////////////

/*
 * Function prototypes
 */
 
/**
 *  @brief   check if a key has been pressed
 *
 * Each pressed key is reported only once
 *
 *  @param   key mask
 *  @return  bit mask where the pressed key is 1
 */
uint8_t get_key_press(uint8_t key_mask);

/**
 *  @brief   check if a key has been long pressed
 *
 * check if a key has been pressed long enough such that the
 * key repeat functionality kicks in. After a small setup delay
 * the key is reported being pressed in subsequent calls
 * to this function. This simulates the user repeatedly
 * pressing and releasing the key.
 *
 *  @param   key mask
 *  @return  bit mask where the pressed key is 1
 */
uint8_t get_key_rpt(uint8_t key_mask);
 
/**
 *  @brief   check if a key is pressed right now
 *
 *  @param   key mask
 *  @return  bit mask where the pressed key is 1
 */
uint8_t get_key_state(uint8_t key_mask);
 
/**
 *  @brief   check if a key has been short pressed
 *
 *  @param   key mask
 *  @return  bit mask where the pressed key is 1
 */
uint8_t get_key_short(uint8_t key_mask);
 
/**
 *  @brief   check if a key has been long pressed
 *
 *  @param   key mask
 *  @return  bit mask where the pressed key is 1
 */
uint8_t get_key_long(uint8_t key_mask);

/**
 *  @brief   initialize the timer and enable timer interrupt
 *
 * Timer 0 is used
 * configured to overflow every 10ms
 *
 *  @param   none
 *  @return  none
 */
void debounce_init();

#endif
