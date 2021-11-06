/*
 * button.c
 *
 *  Created on: Nov 5, 2021
 *      Author: ngocc
 */


#include "button.h"

static int buttonBuffer[NO_OF_BUTTON] = {RELEASED, RELEASED, RELEASED};
static int buttonBufferPrevious[NO_OF_BUTTON] = {RELEASED, RELEASED, RELEASED};

static int pinValue[NO_OF_BUTTON] = {0x0040,0x0080,0x0100};


static int debouncingCounter[NO_OF_BUTTON] = {0,0,0};

static int flagButtonDelay[NO_OF_BUTTON];

void readButton() {
	for(int i = 0; i < NO_OF_BUTTON; i++) {
		if (debouncingCounter[i] > 1) {
			debouncingCounter[i]--;
		} else {
			if (buttonBufferPrevious[i] == HAL_GPIO_ReadPin(BUTTON_PORT, pinValue[i])) {
				buttonBuffer[i] = buttonBufferPrevious[i];
			} else {
				buttonBufferPrevious[i] = HAL_GPIO_ReadPin(BUTTON_PORT, pinValue[i]);
				debouncingCounter[i] = DEBOUNCING_DELAY;
			}
			if (buttonBuffer[i] == RELEASED) {
				flagButtonDelay[i] = 0;
			}
		}
	}
}


int getButtonValue(int button_index) {
	if (button_index > NO_OF_BUTTON) return 0x7fffffff;
	return buttonBuffer[button_index];
}



//this flag can only be pull down if button is released.
void setFlagButtonDelay(int button_index) {
	if (button_index > NO_OF_BUTTON) return;
	flagButtonDelay[button_index] = 1;
}

int getFlagButtonDelay(int button_index) {
	if (button_index > NO_OF_BUTTON) return 0x7fffffff;
	return flagButtonDelay[button_index];

}
