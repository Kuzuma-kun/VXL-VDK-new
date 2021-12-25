/*
 * button.h
 *
 *  Created on: Dec 10, 2021
 *      Author: ngocc
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NUM_OF_BUTTON 	2
#define WAIT_DEBOUNCE	2

#define RELEASE GPIO_PIN_SET
#define PRESS	GPIO_PIN_RESET


void read_button();

int get_button_value(int index);

void set_button_delay(int index);

int get_button_delay(int index);


#endif /* INC_BUTTON_H_ */
