/*
 * clock.c
 *
 *  Created on: Nov 6, 2021
 *      Author: ngocc
 */

#include "clock.h"
#include "button.h"
#include "clock_display.h"


static int hour = 0;
static int minute = 0;
static int second = 0;
static int clock_counter = ONE_SECOND;
static int delay_counter = FIVE_SECOND;

enum fsmState {MODE_0, MODE_1, MODE_2};

enum fsmState fsm_state = MODE_0;

void clock_run() {
	clock_counter--;
	if (clock_counter == 0) {
		clock_counter = ONE_SECOND;
		second = (second + 1) % 12;
		if (second == 0) {
			minute = (minute + 1) % 12;
			if (minute == 0) {
				hour = (hour + 1) % 12;
			}
		}
	}
}

void clock_fsm() {
	switch(fsm_state) {
	case MODE_0:
		if (getButtonValue(0) == PRESSED && getFlagButtonDelay(0) == 0) {
			fsm_state = MODE_1;
			setFlagButtonDelay(0);

		}
		clock_run();
		updateDisplay(hour, minute, second);
		break;
	case MODE_1:
		if (getButtonValue(0) == PRESSED && getFlagButtonDelay(0) == 0) {
			fsm_state = MODE_2;
			setFlagButtonDelay(0);

		}
		else if (getButtonValue(1) == PRESSED && getFlagButtonDelay(1) == 0) {
			hour = (hour + 1) % 12;
			setFlagButtonDelay(1);

		} else if (getButtonValue(2) == PRESSED && getFlagButtonDelay(2) == 0) {
			hour--;
			if (hour < 0) hour = 11;
			setFlagButtonDelay(2);

		}
		updateDisplay(hour, -1, -1);
		break;
	case MODE_2:
		if (getButtonValue(1) == PRESSED && getFlagButtonDelay(1) == 0) {
			minute = (minute + 1) % 12;
			setFlagButtonDelay(1);

		} else if (getButtonValue(2) == PRESSED && getFlagButtonDelay(2) == 0) {
			minute--;
			if (minute < 0) minute = 11;
			setFlagButtonDelay(2);

		}
		updateDisplay(-1, minute, -1);
		break;
	}
	if (getButtonValue(0) == RELEASED &&
		getButtonValue(1) == RELEASED &&
		getButtonValue(2) == RELEASED) {
		delay_counter--;
		if (delay_counter == 0) {
			fsm_state = MODE_0;
		}
	} else {
		if (delay_counter < FIVE_SECOND) {
			delay_counter = FIVE_SECOND;
		}
	}

	displayClock();
}

