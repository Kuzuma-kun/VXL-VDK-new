/*
 * clock_display.h
 *
 *  Created on: Nov 6, 2021
 *      Author: ngocc
 */

#ifndef INC_CLOCK_DISPLAY_H_
#define INC_CLOCK_DISPLAY_H_

#define LED_PORT 		GPIOB
#define LED_START_PIN	0x0001
#define NUM_OF_LED		12

#define TURN_OFF		GPIO_PIN_RESET
#define TURN_ON			GPIO_PIN_SET


void turnOffAll();

void displayClock();

void updateDisplay(int value0, int value1, int value2);


#endif /* INC_CLOCK_DISPLAY_H_ */
