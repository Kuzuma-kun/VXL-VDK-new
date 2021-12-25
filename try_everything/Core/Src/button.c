/*
 * button.c
 *
 *  Created on: Dec 10, 2021
 *      Author: ngocc
 */

#include "main.h"
#include "button.h"

static int buttonPinValue[NUM_OF_BUTTON] = {0x0001, 0x0002, 0x0004};
#define BUTTON_PORT GPIOB

static int buttonBuffer[NUM_OF_BUTTON];
static int buttonPrevBuffer[NUM_OF_BUTTON];

static int buttonWaitTime[NUM_OF_BUTTON];
static int buttonPress1s[NUM_OF_BUTTON];
static int buttonPressCounter[NUM_OF_BUTTON];
static int button_delay[NUM_OF_BUTTON];

void read_button() {
	for(int i = 0; i < NUM_OF_BUTTON; i++) {
		if (buttonWaitTime[i] > 1) {
			buttonWaitTime[i]--;
		} else {
			int temp = HAL_GPIO_ReadPin(BUTTON_PORT, buttonPinValue[i]);

			if (temp == buttonPrevBuffer[i]) {
				buttonBuffer[i] = temp;
			} else {
				buttonWaitTime[i] = WAIT_DEBOUNCE;
				buttonPrevBuffer[i] = temp;
			}

			if (buttonBuffer[i] == PRESS) {
				buttonPressCounter[i]++;
				if (buttonPressCounter[i] < 100) {
					buttonPressCounter[i]++;
				} else {
					buttonPress1s[i] = 1;
				}
			} else {
				buttonPressCounter[i] = 0;
				buttonPress1s[i] = 0;
				button_delay[index] = 0;
			}
		}
	}
}

int get_button_value(int index) {
	return buttonBuffer[index];
}

void set_button_delay(int index) {
	button_delay[index] = 1;
}

int get_button_delay(int index) {
	return button_delay[index];
}

