/*
 * clock_display.c
 *
 *  Created on: Nov 6, 2021
 *      Author: ngocc
 */

#include "main.h"
#include "clock_display.h"

static int clock_buffer[3] = {0, 7, 5};

void turnOffAll() {
	int turnOffGroup = 0;
	for(int i = 0; i < NUM_OF_LED; i++) {
		turnOffGroup = turnOffGroup | (LED_START_PIN << i);
	}
	HAL_GPIO_WritePin(LED_PORT, turnOffGroup, TURN_OFF);
}

void displayClock() {
	turnOffAll();
	if (clock_buffer[0] != -1) {
		HAL_GPIO_WritePin(LED_PORT, LED_START_PIN << clock_buffer[0], TURN_ON);
	}
	if (clock_buffer[1] != -1) {
		HAL_GPIO_WritePin(LED_PORT, LED_START_PIN << clock_buffer[1], TURN_ON);
	}
	if (clock_buffer[2] != -1) {
		HAL_GPIO_WritePin(LED_PORT, LED_START_PIN << clock_buffer[2], TURN_ON);
	}
}

void updateDisplay(int value0, int value1, int value2) {
	clock_buffer[0] = value0;
	clock_buffer[1] = value1;
	clock_buffer[2] = value2;
}
