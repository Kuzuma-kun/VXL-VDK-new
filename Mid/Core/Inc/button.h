/*
 * button.h
 *
 *  Created on: Nov 5, 2021
 *      Author: ngocc
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NO_OF_BUTTON 3
#define BUTTON_PORT 	GPIOA

#define PRESSED 	GPIO_PIN_RESET
#define RELEASED 	GPIO_PIN_SET

#define DEBOUNCING_DELAY	2

void readButton();

int getButtonValue(int button_index);

//this flag can only be pull down if button is released.
void setFlagButtonDelay(int button_index);
int getFlagButtonDelay(int button_index);

#endif /* INC_BUTTON_H_ */
